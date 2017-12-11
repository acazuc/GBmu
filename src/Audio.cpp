#include "Audio.h"
#include "Main.h"
#include <memboy.h>
#include <iostream>
#include <unistd.h>
#include <climits>
#include <cmath>

#define CLOCK_FREQ 4194304

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
static uint64_t c1lastswptick = 0;
static uint64_t c1lastenvtick = 0;
static uint64_t c2lastenvtick = 0;
static uint64_t c4lastenvtick = 0;

static uint64_t c4nextclocktick = 0;
static uint16_t c4stepcounter = 0;
static uint16_t c4stepstate = 0xffff;
static float c4divider = 1;

/*static uint8_t NR10 = 0b00001001;
static uint8_t NR11 = 0b10101010;
static uint8_t NR12 = 0b10011011;
static uint8_t NR13 = 0b00000000;
static uint8_t NR14 = 0b00100000;

static uint8_t NR21 = 0b10101010;
static uint8_t NR22 = 0b10011011;
static uint8_t NR23 = 0b10101101;
static uint8_t NR24 = 0b10100011;

static uint8_t NR30 = 0b10000000;
static uint8_t NR31 = 0b00000000;
static uint8_t NR32 = 0b00100000;
static uint8_t NR33 = 0b11011111;
static uint8_t NR34 = 0b10000111;

static uint8_t NR41 = 0b00000000;
static uint8_t NR42 = 0b11110111;
static uint8_t NR43 = 0b01100000;
static uint8_t NR44 = 0b10000000;

static uint8_t NR50 = 0b00100010;
static uint8_t NR51 = 0b00100010;
static uint8_t NR52 = 0b00000010;*/

static uint64_t clockCount = 0;
static uint64_t nextClock = 0;
static uint64_t envtick = 0;
static uint64_t swptick = 0;

static memboy mem;

static uint32_t c1regtofreq(uint8_t nr13, uint8_t nr14)
{
	uint16_t reg = (uint16_t)nr13 | (((uint16_t)(nr14 & 0x7)) << 8);
	return (CLOCK_FREQ / (32 * (2048 - reg)));
}

static uint16_t c1freqtoval(uint32_t freq)
{
	return (2048 - CLOCK_FREQ / (32 * freq));
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
	return (CLOCK_FREQ / (32 * (2048 - reg)));
}

static uint32_t c3regtofreq(uint8_t nr33, uint8_t nr34)
{
	uint16_t reg = (uint16_t)nr33 | (((uint16_t)(nr34 & 0x7)) << 8);
	return (CLOCK_FREQ / (32 * (2048 - reg)));
}

static int16_t getc1val()
{
	if (mem[NR14] & 0b10000000)
	{
		c1len = 64 - (mem[NR11] & 0b00111111);
		c1env = (mem[NR12] & 0b11110000) >> 4;
		c1freq = c1regtofreq(mem[NR13], mem[NR14]);
		mem[NR14] = mem[NR14] & 0b01111111;
	}
	uint8_t duty = (mem[NR11] & 0b11000000) >> 6;
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
	if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SIN)
	{
		float a = curr / (float)inter - dutyper;
		if (a > 0)
			return (SHRT_MAX * sin(a / (1 - dutyper) * M_PI) * envfac);
		return (SHRT_MIN * sin(-a / (dutyper) * M_PI) * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SAW)
	{
		return (SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (inter - curr) / (float)inter * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SQUARE)
	{
		if (curr / (float)inter > dutyper)
			return (SHRT_MAX * envfac);
		return (SHRT_MIN * envfac);
	}
}

static int16_t getc2val()
{
	if (mem[NR24] & 0b10000000)
	{
		c2len = 64 - (mem[NR21] & 0b00111111);
		c2env = (mem[NR22] & 0b11110000) >> 4;
		mem[NR24] = mem[NR24] & 0b01111111;
	}
	c2freq = c2regtofreq(mem[NR23], mem[NR24]);
	uint8_t duty = (mem[NR21] & 0b11000000) >> 6;
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
	if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SIN)
	{
		float a = curr / (float)inter - dutyper;
		if (a > 0)
			return (SHRT_MAX * sin(a / (1 - dutyper) * M_PI) * envfac);
		return (SHRT_MIN * sin(-a / (dutyper) * M_PI) * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SAW)
	{
		return (SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (inter - curr) / (float)inter * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SQUARE)
	{
		if (curr / (float)inter > dutyper)
		return (SHRT_MIN * envfac);
			return (SHRT_MAX * envfac);
	}
}

static int16_t getc3val()
{
	if (!(mem[NR30] & 0b10000000))
	{
		mem[NR52] = mem[NR52] & 0b11111011;
		return (0);
	}
	if (mem[NR34] & 0b10000000)
	{
		c3len = 256 - mem[NR31];
		c3freq = c3regtofreq(mem[NR33], mem[NR34]);
		mem[NR34] = (mem[NR34] & 0b01111111);
	}
	if (!(mem[NR34] & 0b01000000))
		c3freq = c3regtofreq(mem[NR33], mem[NR34]);
	uint32_t inter = freq / c3freq;
	if (!inter)
		return (0);
	uint8_t idx = (frame % inter) / (float)inter * 32;
	uint8_t tmp = mem[0xFF30 + idx / 2];
	if (!(idx & 1))
		tmp = tmp >> 4;
	tmp &= 0xf;
	uint8_t idx1 = (idx + 1) % 32;
	uint8_t tmp1 = mem[0xFF30 + idx1 / 2];
	if (!(idx1 & 1))
		tmp1 = tmp1 >> 4;
	tmp1 &= 0xf;
	int16_t data = SHRT_MIN + (SHRT_MAX - SHRT_MIN) * tmp / 0xf;
	int16_t data1 = SHRT_MIN + (SHRT_MAX - SHRT_MIN) * tmp1 / 0xf;
	float interpfac = ((frame % inter) / (float)inter * 32) - idx;
	int16_t val = data + (data1 - data) * interpfac;
	uint8_t level = (mem[NR32] & 0b01100000) >> 5;
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
	if (mem[NR44] & 0b10000000)
	{
		c4stepstate = 0xff;
		c4stepcounter = 0;
		c4len = 64 - (mem[NR41] & 0b00111111);
		uint8_t tmp = mem[NR43] & 0b00000111;
		if (tmp == 0b000)
			c4divider = .5;
		else
			c4divider = tmp;
		c4divider *= pow(2, ((mem[NR43] & 0b11110000) >> 4) + 1);
		c4nextclocktick = frame + freq / (524288 / c4divider);
		c4env = (mem[NR42] & 0b11110000) >> 4;
		mem[NR44] = mem[NR44] & 0b01111111;
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
		if (mem[NR43] & 0b00001000)
			c4stepstate = (c4stepstate & 0b0111111) | (xored << 6);
		c4nextclocktick = frame + freq / (524288 / c4divider);
		++c4stepcounter;
	}
	float envfac = c4env / 15.;
	if (c4stepstate & 0x1)
		return (SHRT_MAX * envfac);
	return (SHRT_MIN * envfac);
}

static void updateLengthTick()
{
	//Channel 1
	if (mem[NR14] & 0b01000000)
	{
		if (c1len == 0)
			mem[NR52] = mem[NR52] & 0b11111110;
		else
			c1len--;
	}
	//Channel 2
	if (mem[NR24] & 0b01000000)
	{
		if (c2len == 0)
			mem[NR52] = mem[NR52] & 0b11111101;
		else
			c2len--;
	}
	//Channel 3
	if (mem[NR34] & 0b01000000)
	{
		if (c3len == 0)
			mem[NR52] = mem[NR52] & 0b11111011;
		else
			c3len--;
	}
	//Channel 4
	if (mem[NR44] & 0b01000000)
	{
		if (c4len == 0)
			mem[NR52] = mem[NR52] & 0b11110111;
		else
			c4len--;
	}
}

static void updateEnvTick()
{
	//Channel 1
	{
		uint8_t envstep = mem[NR12] & 0b00000111;
		if (envstep != 0 && envtick - c1lastenvtick > envstep)
		{
			c1lastenvtick = envtick;
			bool direction = mem[NR12] & 0b00001000;
			if (direction)
			{
				if (c1env != 0b1111)
					c1env++;
			}
			else
			{
				if (c1env == 0)
					mem[NR52] = mem[NR52] & 0b11111110;
				else
					c1env--;
			}
		}
	}
	//Channel 2
	{
		uint8_t envstep = mem[NR22] & 0b00000111;
		if (envstep != 0 && envtick - c2lastenvtick > envstep)
		{
			c2lastenvtick = envtick;
			bool direction = mem[NR22] & 0b00001000;
			if (direction)
			{
				if (c2env != 0b1111)
					c2env++;
			}
			else
			{
				if (c2env == 0)
					mem[NR52] = mem[NR52] & 0b11111101;
				else
					c2env--;
			}
		}
	}
	//Channel 4
	{
		uint8_t envstep = mem[NR42] & 0b00000111;
		if (envstep != 0 && envtick - c4lastenvtick > envstep)
		{
			c4lastenvtick = envtick;
			bool direction = mem[NR42] & 0b00001000;
			if (direction)
			{
				if (c4env != 0b1111)
					c4env++;
			}
			else
			{
				if (c4env == 0)
					mem[NR52] = mem[NR52] & 0b11110111;
				else
					c4env--;
			}
		}
	}
}

static void updateSweepTick()
{
	//Channel 1
	{
		uint8_t swptime = mem[NR10] & 0b01110000;
		if (swptime != 0 && swptick - c1lastswptick > swptime)
		{
			c1lastswptick = swptick;
			bool direction = mem[NR10] & 0b00001000;
			uint8_t swpshift = mem[NR10] & 0b00000111;
			if (direction)
			{
				int32_t newfreq = c1freq + c1freq / pow(2, swpshift);
				if (newfreq && c1freqtoval(newfreq) > 2047)
					newfreq = 2047;
				c1freq = newfreq;
			}
			else
			{
				int32_t newfreq = c1freq - c1freq / pow(2, swpshift);
				if (newfreq < 0)
					newfreq = 0;
				c1freq = newfreq;
			}
		}
	}
}

static int paCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *paTimeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	(void)input;
	(void)paTimeInfo;
	(void)statusFlags;
	frameCount *= 2;
	int16_t *out = (int16_t*)output;
	for (unsigned long i = 0; i < frameCount; ++i)
	{
		out[i] = 0;
		if (mem[NR52] & 0b10000000)
		{
			bool c1on = (mem[NR51] & 0b00010001) && (mem[NR52] & 0b00000001);
			bool c2on = (mem[NR51] & 0b00100010) && (mem[NR52] & 0b00000010);
			bool c3on = (mem[NR51] & 0b01000100) && (mem[NR52] & 0b00000100);
			bool c4on = (mem[NR51] & 0b10001000) && (mem[NR52] & 0b00001000);
			int16_t c1 = c1on ? getc1val() : 0;
			int16_t c2 = c2on ? getc2val() : 0;
			int16_t c3 = c3on ? getc3val() : 0;
			int16_t c4 = c4on ? getc4val() : 0;
			mem[PCM12] = ((uint8_t)(c1 / 0xff / 2 + CHAR_MIN) + (uint8_t)(c2 / 0xff / 2 + CHAR_MIN));
			mem[PCM34] = ((uint8_t)(c3 / 0xff / 2 + CHAR_MIN) + (uint8_t)(c4 / 0xff / 2 + CHAR_MIN));
			if (i & 0x1)
			{
				bool lc1on = c1on && (mem[NR51] & 0b00000001);
				bool lc2on = c2on && (mem[NR51] & 0b00000010);
				bool lc3on = c3on && (mem[NR51] & 0b00000100);
				bool lc4on = c4on && (mem[NR51] & 0b00001000);
				if (lc1on)
					out[i] += c1 / 4;
				if (lc2on)
					out[i] += c2 / 4;
				if (lc3on)
					out[i] += c3 / 4;
				if (lc4on)
					out[i] += c4 / 4;
				out[i] *= ((mem[NR50] & 0b00000111) >> 0) / 7.;
			}
			else
			{
				bool lc1on = c1on && (mem[NR51] & 0b00010000);
				bool lc2on = c2on && (mem[NR51] & 0b00100000);
				bool lc3on = c3on && (mem[NR51] & 0b01000000);
				bool lc4on = c4on && (mem[NR51] & 0b10000000);
				if (lc1on)
					out[i] += c1 / 4;
				if (lc2on)
					out[i] += c2 / 4;
				if (lc3on)
					out[i] += c3 / 4;
				if (lc4on)
					out[i] += c4 / 4;
				out[i] *= ((mem[NR50] & 0b01110000) >> 4) / 7.;
			}
		}
		if (frame >= nextClock)
		{
			if (clockCount & 0x1)
				updateLengthTick();
			if (clockCount & 0x7 == 0)
			{
				updateEnvTick();
				envtick++;
			}
			if ((clockCount + 1) % 4 == 3)
			{
				updateSweepTick();
				swptick++;
			}
			clockCount++;
			nextClock += freq / 512;
		}
		if (i & 0x1)
			++frame;
	}
	return (paContinue);
}

Audio::Audio()
: c12type(AUDIO_C12_TYPE_SQUARE)
{
	//triangle
	mem[0xFF30] = 0x01;
	mem[0xFF31] = 0x23;
	mem[0xFF32] = 0x45;
	mem[0xFF33] = 0x67;
	mem[0xFF34] = 0x89;
	mem[0xFF35] = 0xAB;
	mem[0xFF36] = 0xCD;
	mem[0xFF37] = 0xEF;
	mem[0xFF38] = 0xED;
	mem[0xFF39] = 0xCB;
	mem[0xFF3A] = 0xA9;
	mem[0xFF3B] = 0x87;
	mem[0xFF3C] = 0x65;
	mem[0xFF3D] = 0x43;
	mem[0xFF3E] = 0x32;
	mem[0xFF3F] = 0x10;

	mem[NR10] = 0b10111111;
	mem[NR11] = 0b10101010;
	mem[NR12] = 0b10011011;
	mem[NR13] = 0b10101100;
	mem[NR14] = 0b10100011;

	mem[NR21] = 0b10101010;
	mem[NR22] = 0b10011011;
	mem[NR23] = 0b10101001;
	mem[NR24] = 0b10100011;

	mem[NR30] = 0b10000000;
	mem[NR31] = 0b00000000;
	mem[NR32] = 0b00100000;
	mem[NR33] = 0b11011111;
	mem[NR34] = 0b10000001;

	mem[NR41] = 0b00001111;
	mem[NR42] = 0b11111111;
	mem[NR43] = 0b01100000;
	mem[NR44] = 0b11000000;

	mem[NR50] = 0b00010001;
	mem[NR51] = 0b10001000;
	mem[NR52] = 0b10001000;

	PaStreamParameters parameters;
	parameters.device = Pa_GetDefaultOutputDevice();
	parameters.channelCount = 2;
	parameters.suggestedLatency = 2;
	parameters.sampleFormat = paInt16;
	parameters.hostApiSpecificStreamInfo = 0;
	PaError error = Pa_OpenStream(&this->stream, 0, &parameters, freq, 1000, paNoFlag, paCallback, this);
	if (error)
	{
		std::cerr << "Failed to create stream" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Audio::~Audio()
{
	Pa_CloseStream(this->stream);
}

void Audio::start()
{
	Pa_StartStream(this->stream);
}
