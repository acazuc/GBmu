#include "Audio.h"
#include "Main.h"
#include <iostream>
#include <unistd.h>
#include <climits>
#include <cmath>

static uint64_t freq = 100000;
static uint64_t frame = 0;

static uint64_t c1len = 0;
static uint64_t c2len = 0;
static uint64_t c3len = 0;
static uint64_t c4len = 0;
static uint64_t c1env = 0;
static uint64_t c2env = 0;
static uint64_t c3env = 0;
static uint64_t c4env = 0;
static uint64_t c1freq = 0;
static uint64_t c2freq = 0;
static uint64_t c3freq = 0;
static uint64_t c1nextenvstepchange = 0;
static uint64_t c1nextswpstepchange = 0;
static uint64_t c2nextenvstepchange = 0;
static uint64_t c4nextenvstepchange = 0;

static uint64_t c4nextclocktick = 0;
static uint16_t c4stepcounter = 0;
static uint16_t c4stepstate = 0xffff;
static float c4divider = 1;

static uint8_t NR10 = 0b00001001;
static uint8_t NR11 = 0b10101010;
static uint8_t NR12 = 0b10011011;
static uint8_t NR13 = 0b00000000;
static uint8_t NR14 = 0b00100000;

static uint8_t NR21 = 0b11101010;
static uint8_t NR22 = 0b10011011;
static uint8_t NR23 = 0b10101101;
static uint8_t NR24 = 0b00100011;

static uint8_t NR30 = 0b10000000;
static uint8_t NR31 = 0b00000000;
static uint8_t NR32 = 0b00100000;
static uint8_t NR33 = 0b11011111;
static uint8_t NR34 = 0b10000111;

static uint8_t NR41 = 0b00000000;
static uint8_t NR42 = 0b11110111;
static uint8_t NR43 = 0b01100000;
static uint8_t NR44 = 0b10000000;

static uint8_t NR50 = 0b01000100;
static uint8_t NR51 = 0b01000100;
static uint8_t NR52 = 0b10000100;


static uint8_t mem[0xFFFF];

static uint32_t c1regtofreq(uint8_t nr13, uint8_t nr14)
{
	uint16_t reg = (uint16_t)nr13 | (((uint16_t)(nr14 & 0x7)) << 8);
	return (4194304 / (32 * (2048 - reg)));
}

static uint16_t c1freqtoval(uint32_t freq)
{
	return (2048 - 4194304 / (32 * freq));
}

static void c1freqtoreg(uint32_t freq, uint8_t *nr13, uint8_t *nr14)
{
	uint16_t reg = c1freqtoval(freq);
	*nr13 = reg & 0xff;
	*nr14 = (*nr14 & 0b11111000) | (reg >> 8);
}

static uint32_t c2regtofreq(uint8_t nr23, uint8_t nr24)
{
	uint16_t reg = (uint16_t)nr23 | (((uint16_t)(nr24 & 0x7)) << 8);
	return (4194304 / (32 * (2048 - reg)));
}

static uint16_t c2freqtoval(uint32_t freq)
{
	return (2048 - 4194304 / (32 * freq));
}

static void c2freqtoreg(uint32_t freq, uint8_t *nr23, uint8_t *nr24)
{
	uint16_t reg = c2freqtoval(freq);
	*nr23 = reg & 0xff;
	*nr24 = (*nr24 & 0b11111000) | (reg >> 8);
}

static uint32_t c3regtofreq(uint8_t nr33, uint8_t nr34)
{
	uint16_t reg = (uint16_t)nr33 | (((uint16_t)(nr34 & 0x7)) << 8);
	return (4194304 / (32 * (2048 - reg)));
}

static int16_t getc1val()
{
	if (NR14 & 0b10000000)
	{
		c1len = (64 - (NR11 & 0b00111111)) * freq / 256;
		c1env = (NR12 & 0b11110000) >> 4;
		c1freq = c1regtofreq(NR13, NR14);
		NR14 &= 0b01111111;
	}
	if (NR14 & 0b01000000)
	{
		if (c1len == 0)
		{
			NR52 &= 0b11111110;
			return (0);
		}
		else
		{
			c1len--;
		}
	}
	if (frame >= c1nextenvstepchange)
	{
		uint8_t envstep = NR12 & 0b00000111;
		if (envstep != 0)
		{
			c1nextenvstepchange = frame + envstep * freq / 64;
			bool goUp = NR12 & 0b00001000;
			if (goUp)
			{
				if (c1env != 0b1111)
					c1env++;
			}
			else
			{
				if (c1env == 0)
					NR52 &= 0b11111110;
				else
					c1env--;
			}
		}
	}
	if (frame >= c1nextswpstepchange)
	{
		uint8_t swptime = NR10 & 0b01110000;
		if (swptime != 0)
		{
			c1nextswpstepchange = frame + swptime * freq / 128;
			bool goUp = NR10 & 0b00001000;
			uint8_t swpShift = NR12 & 0b00000111;
			if (goUp)
			{
				int32_t newfreq = c1freq + c1freq / pow(2, swpShift);
				if (c1freqtoval(newfreq) > 2047)
					newfreq = 2047;
				c1freq = newfreq;
			}
			else
			{
				int32_t newfreq = c1freq - c1freq / pow(2, swpShift);
				if (newfreq < 0)
					newfreq = 0;
				c1freq = newfreq;
			}
		}
	}
	uint8_t duty = (NR11 & 0b11000000) >> 6;
	float dutyper = 0;
	if (duty == 0b11)
		dutyper = .25;
	else if (duty == 0b10)
		dutyper = .5;
	else if (duty == 0b01)
		dutyper = .75;
	else if (duty == 0b00)
		dutyper = .875;
	uint32_t inter = freq / c1freq;
	uint32_t curr = frame % inter;
	float envfac = c1env / 15.;
	if (curr / (float)inter > dutyper)
		return (SHRT_MAX * envfac);
	else
		return (SHRT_MIN * envfac);
}

static int16_t getc2val()
{
	if (NR24 & 0b10000000)
	{
		c2len = (64 - (NR21 & 0b00111111)) * freq / 256;
		c2env = (NR22 & 0b11110000) >> 4;
		NR24 &= 0b01111111;
	}
	c2freq = c2regtofreq(NR23, NR24);
	if (NR24 & 0b01000000)
	{
		if (c2len == 0)
		{
			NR52 &= 0b11111101;
			return (0);
		}
		else
		{
			c2len--;
		}
	}
	if (frame >= c1nextenvstepchange)
	{
		uint8_t envstep = NR22 & 0b00000111;
		if (envstep != 0)
		{
			c2nextenvstepchange = frame + envstep * freq / 64;
			bool goUp = NR22 & 0b00001000;
			if (goUp)
			{
				if (c2env != 0b1111)
					c2env++;
			}
			else
			{
				if (c2env == 0)
					NR52 &= 0b11111101;
				else
					c2env--;
			}
		}
	}
	uint8_t duty = (NR21 & 0b11000000) >> 6;
	float dutyper = 0;
	if (duty == 0b11)
		dutyper = .25;
	else if (duty == 0b10)
		dutyper = .5;
	else if (duty == 0b01)
		dutyper = .75;
	else if (duty == 0b00)
		dutyper = .875;
	uint32_t inter = freq / c2freq;
	uint32_t curr = frame % inter;
	float envfac = c2env / 15.;
	if (curr / (float)inter > dutyper)
		return (SHRT_MAX * envfac);
	return (SHRT_MIN * envfac);
}

static int16_t getc3val()
{
	if (!(NR30 & 0b10000000))
	{
		NR52 &= 0b11111011;
		return (0);
	}
	if (NR34 & 0b10000000)
	{
		c3len = (256 - NR31) * freq / 256;
		c3freq = c3regtofreq(NR33, NR34);
		NR34 &= 0b01111111;
	}
	if (NR34 & 0b01000000)
	{
		if (c3len == 0)
		{
			NR52 &= 0b11111011;
			return (0);
		}
		else
		{
			c3len--;
		}
	}
	else
	{
		c3freq = c3regtofreq(NR33, NR34);
	}
	uint32_t inter = freq / c3freq;
	if (!inter)
		return (0);
	uint8_t idx = (frame % inter) / (float)inter * 32;
	uint8_t tmp = mem[0xFF30 + idx / 2];
	if (!(idx & 1))
		tmp = tmp >> 4;
	tmp &= 0xF;
	float fac = tmp / 16.;
	int16_t val = -SHRT_MIN;
	val += (SHRT_MAX - SHRT_MIN) * fac;
	uint8_t level = (NR32 & 0b01100000) >> 5;
	if (level == 0)
		return (0);
	if (level == 1)
		return (val);
	if (level == 2)
		return (val / 2);
	return (val / 4);
}

static int16_t getc4val()
{
	if (NR44 & 0b10000000)
	{
		c4stepstate = 0xff;
		c4stepcounter = 0;
		c4len = (64 - (NR41 & 0b00111111)) * freq / 256;
		uint8_t tmp = NR43 & 0b00000111;
		if (tmp == 0b000)
			c4divider = .5;
		else
			c4divider = tmp;
		c4divider *= pow(2, ((NR43 & 0b11110000) >> 4) + 1);
		c4nextclocktick = frame + freq / (524288 / c4divider);
		c4env = (NR42 & 0b11110000) >> 4;
		NR44 &= 0b01111111;
	}
	if (NR44 & 0b01000000)
	{
		if (c4len == 0)
		{
			NR52 &= 0b11110111;
			return (0);
		}
		else
		{
			c4len--;
		}
	}
	if (frame >= c4nextenvstepchange)
	{
		uint8_t envstep = NR22 & 0b00000111;
		if (envstep != 0)
		{
			c4nextenvstepchange = frame + envstep * freq / 64;
			bool goUp = NR42 & 0b00001000;
			if (goUp)
			{
				if (c4env != 0b1111)
					c4env++;
			}
			else
			{
				if (c4env == 0)
					NR52 &= 0b11110111;
				else
					c4env--;
			}
		}
	}
	if (frame >= c4nextclocktick)
	{
		if (c4stepcounter > 32767)
		{
			c4stepcounter = 0;
			c4stepstate = 0xffff;
		}
		uint8_t xored = (c4stepstate & 0x1) ^ ((c4stepstate & 0x2) >> 1);
		c4stepstate = c4stepstate >> 1;
		c4stepstate = (c4stepstate & 0b011111111111111) | (xored << 14);
		if (NR43 & 0b00001000)
			c4stepstate = (c4stepstate & 0b0111111) | (xored << 6);
		c4nextclocktick = frame + freq / (524288 / c4divider);
		++c4stepcounter;
	}
	float envfac = c4env / 15.;
	if (c4stepstate & 0x1)
		return (SHRT_MAX * envfac);
	return (SHRT_MIN * envfac);
}

static int paCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *paTimeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	(void)input;
	(void)output;
	(void)frameCount;
	(void)paTimeInfo;
	(void)statusFlags;
	(void)userData;
	frameCount *= 2;
	int16_t *out = (int16_t*)output;
	for (unsigned long i = 0; i < frameCount; ++i)
	{
		out[i] = 0;
		if (NR52 & 0b10000000)
		{
			bool c1on = (NR51 & 0b00010001) && (NR52 & 0b00000001);
			bool c2on = (NR51 & 0b00100010) && (NR52 & 0b00000010);
			bool c3on = (NR51 & 0b01000100) && (NR52 & 0b00000100);
			bool c4on = (NR51 & 0b10001000) && (NR52 & 0b00001000);
			int16_t c1 = 0;
			int16_t c2 = 0;
			int16_t c3 = 0;
			int16_t c4 = 0;
			if (c1on)
				c1 = getc1val();
			if (c2on)
				c2 = getc2val();
			if (c3on)
				c3 = getc3val();
			if (c4on)
				c4 = getc4val();
			if (i & 0x1)
			{
				bool lc1on = c1on && (NR51 & 0b00000001);
				bool lc2on = c2on && (NR51 & 0b00000010);
				bool lc3on = c3on && (NR51 & 0b00000100);
				bool lc4on = c4on && (NR51 & 0b00001000);
				if (lc1on)
					out[i] += c1 / 4;
				if (lc2on)
					out[i] += c2 / 4;
				if (lc3on)
					out[i] += c3 / 4;
				if (lc4on)
					out[i] += c4 / 4;
				out[i] *= ((NR50 & 0b00000111) >> 0) / 7.;
			}
			else
			{
				bool lc1on = c1on && (NR51 & 0b00010000);
				bool lc2on = c2on && (NR51 & 0b00100000);
				bool lc3on = c3on && (NR51 & 0b01000000);
				bool lc4on = c4on && (NR51 & 0b10000000);
				if (lc1on)
					out[i] += c1 / 4;
				if (lc2on)
					out[i] += c2 / 4;
				if (lc3on)
					out[i] += c3 / 4;
				if (lc4on)
					out[i] += c4 / 4;
				out[i] *= ((NR50 & 0b01110000) >> 4) / 7.;
			}
		}
		if (i & 0x1)
			++frame;
	}
	return (paContinue);
}

Audio::Audio()
{
	*((uint32_t*)&(mem[0xFF30])) = 0x01234567;
	*((uint32_t*)&(mem[0xFF34])) = 0x89ABCDEF;
	*((uint32_t*)&(mem[0xFF38])) = 0xEDCBA987;
	*((uint32_t*)&(mem[0xFFFC])) = 0x65432100; 
	PaStreamParameters parameters;
	parameters.device = Pa_GetDefaultOutputDevice();
	parameters.channelCount = 2;
	parameters.sampleFormat = paInt16;
	parameters.suggestedLatency = 0.2;
	parameters.hostApiSpecificStreamInfo = 0;
	PaError error = Pa_OpenStream(&this->stream, 0, &parameters, freq, 10, paNoFlag, paCallback, this);
	if (error)
	{
		std::cerr << "Failed to create stream" << std::endl;
		exit(EXIT_FAILURE);
	}
	Pa_StartStream(this->stream);
}
