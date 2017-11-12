#include "Audio.h"
#include "Main.h"
#include <iostream>
#include <unistd.h>
#include <climits>
#include <cmath>

static uint64_t freq = 100000;
static uint64_t frame = 0;

static uint64_t c1nextenvstepchange = 0;
static uint64_t c1nextswpstepchange = 0;
static uint64_t c2nextenvstepchange = 0;

static uint8_t NR10 = 0b00001001;
static uint8_t NR11 = 0b10101010;
static uint8_t NR12 = 0b10011011;
static uint8_t NR13 = 0b00000000;
static uint8_t NR14 = 0b00100000;

static uint8_t NR21 = 0b11101010;
static uint8_t NR22 = 0b10011011;
static uint8_t NR23 = 0b10101101;
static uint8_t NR24 = 0b00100011;

static uint8_t NR41 = 0b00000000;
static uint8_t NR42 = 0b00000000;
static uint8_t NR43 = 0b00000000;
static uint8_t NR44 = 0b00000000;

static uint8_t NR50 = 0b00010001;
static uint8_t NR51 = 0b00100001;
static uint8_t NR52 = 0b10000011;

static uint32_t c1regtofreq(uint8_t nr13, uint8_t nr14)
{
	uint16_t reg = (uint16_t)nr13 | (((uint16_t)(nr14 & 0x7)) << 8);
	return (4194304 / (4 * 2 * (2048 - reg)));
}

static uint16_t c1freqtoval(uint32_t freq)
{
	return (2048 - 4194304 / (4 * 2 * freq));
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
	return (4194304 / (4 * 2 * (2048 - reg)));
}

static uint16_t c2freqtoval(uint32_t freq)
{
	return (2048 - 4194304 / (4 * 2 * freq));
}

static void c2freqtoreg(uint32_t freq, uint8_t *nr23, uint8_t *nr24)
{
	uint16_t reg = c2freqtoval(freq);
	*nr23 = reg & 0xff;
	*nr24 = (*nr24 & 0b11111000) | (reg >> 8);
}

static int16_t getc1val()
{
	uint32_t c1freq = c1regtofreq(NR13, NR14);
	if (frame >= c1nextenvstepchange)
	{
		uint8_t envstep = NR12 & 0b00000111;
		if (envstep != 0)
		{
			c1nextenvstepchange = frame + envstep * freq / 64;
			bool goUp = NR12 & 0b00001000;
			uint8_t soundVal = (NR12 & 0b11110000) >> 4;
			if (goUp)
			{
				if (soundVal != 0b1111)
					soundVal++;
			}
			else
			{
				if (soundVal != 0)
					soundVal--;
			}
			NR12 = (NR12 & 0b00001111) | (soundVal << 4);
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
	c1freqtoreg(c1freq, &NR13, &NR14);
	float envVal = ((NR12 & 0b11110000) >> 4) / 15.;
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
	uint32_t curr = frame & inter;
	if (curr / (float)inter > dutyper)
		return (SHRT_MAX * envVal);
	else
		return (SHRT_MIN * envVal);
}

static int16_t getc2val()
{
	uint32_t c2freq = c1regtofreq(NR23, NR24);
	if (frame >= c1nextenvstepchange)
	{
		uint8_t envstep = NR22 & 0b00000111;
		if (envstep != 0)
		{
			c2nextenvstepchange = frame + envstep * freq / 64;
			bool goUp = NR22 & 0b00001000;
			uint8_t soundVal = (NR22 & 0b11110000) >> 4;
			if (goUp)
			{
				if (soundVal != 0b1111)
					soundVal++;
			}
			else
			{
				if (soundVal != 0)
					soundVal--;
			}
			NR22 = (NR22 & 0b00001111) | (soundVal << 4);
		}
	}
	c2freqtoreg(c2freq, &NR23, &NR24);
	float envVal = ((NR22 & 0b11110000) >> 4) / 15.;
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
	uint32_t curr = frame & inter;
	if (curr / (float)inter > dutyper)
		return (SHRT_MAX * envVal);
	else
		return (SHRT_MIN * envVal);
}

static int16_t getc3val()
{
	return (0);
}

static int16_t getc4val()
{
	//
	return (0);
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
			int16_t c1 = 0;
			int16_t c2 = 0;
			int16_t c3 = 0;
			int16_t c4 = 0;
			bool c1on = (NR51 & 0b00010001) && (NR52 & 0b00000001);
			bool c2on = (NR51 & 0b00100010) && (NR52 & 0b00000010);
			bool c3on = (NR51 & 0b01000100) && (NR52 & 0b00000100);
			bool c4on = (NR51 & 0b10001000) && (NR52 & 0b00001000);
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
				uint8_t nb = (lc1on ? 1 : 0) + (lc2on ? 1 : 0) + (lc3on ? 1 : 0) + (lc4on ? 1 : 0);
				if (nb)
				{
					if (lc1on)
						out[i] += c1 / nb;
					if (lc2on)
						out[i] += c2 / nb;
					if (lc3on)
						out[i] += c3 / nb;
					if (lc4on)
						out[i] += c4 / nb;
					out[i] *= ((NR50 & 0b00000111) >> 0) / 7.;
				}
			}
			else
			{
				bool lc1on = c1on && (NR51 & 0b00010000);
				bool lc2on = c2on && (NR51 & 0b00100000);
				bool lc3on = c3on && (NR51 & 0b01000000);
				bool lc4on = c4on && (NR51 & 0b10000000);
				uint8_t nb = (lc1on ? 1 : 0) + (lc2on ? 1 : 0) + (lc3on ? 1 : 0) + (lc4on ? 1 : 0);
				if (nb)
				{
					if (lc1on)
						out[i] += c1 / nb;
					if (lc2on)
						out[i] += c2 / nb;
					if (lc3on)
						out[i] += c3 / nb;
					if (lc4on)
						out[i] += c4 / nb;
					out[i] *= ((NR50 & 0b01110000) >> 4) / 7.;
				}
			}
		}
		if (i & 0x1)
			++frame;
	}
	return (paContinue);
}

Audio::Audio()
{
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
