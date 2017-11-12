#include "Audio.h"
#include "Main.h"
#include <iostream>
#include <unistd.h>
#include <climits>
#include <cmath>

static uint64_t freq = 100000;
static uint64_t frame = 0;

static uint64_t c0nextenvstepchange = 0;
static uint64_t c0nextswpstepchange = 0;
static uint64_t c1nextenvstepchange = 0;

static uint8_t NR10 = 0b00001001;
static uint8_t NR11 = 0b10101010;
static uint8_t NR12 = 0b10011011;
static uint8_t NR13 = 0b00000000;
static uint8_t NR14 = 0b00100000;
static uint8_t NR21 = 0b11101010;
static uint8_t NR22 = 0b10011011;
static uint8_t NR23 = 0b10101101;
static uint8_t NR24 = 0b00100111;

static uint32_t c0regtofreq(uint8_t nr13, uint8_t nr14)
{
	uint16_t reg = (uint16_t)nr13 | (((uint16_t)(nr14 & 0x7)) << 8);
	return (4194304 / (4 * 2 * (2048 - reg)));
}

static uint16_t c0freqtoval(uint32_t freq)
{
	return (2048 - 4194304 / (4 * 2 * freq));
}

static void c0freqtoreg(uint32_t freq, uint8_t *nr13, uint8_t *nr14)
{
	uint16_t reg = c0freqtoval(freq);
	*nr13 = reg & 0xff;
	*nr14 = (*nr14 & 0b11111000) | (reg >> 8);
}

static uint32_t c1regtofreq(uint8_t nr23, uint8_t nr24)
{
	uint16_t reg = (uint16_t)nr23 | (((uint16_t)(nr24 & 0x7)) << 8);
	return (4194304 / (4 * 2 * (2048 - reg)));
}

static uint16_t c1freqtoval(uint32_t freq)
{
	return (2048 - 4194304 / (4 * 2 * freq));
}

static void c1freqtoreg(uint32_t freq, uint8_t *nr23, uint8_t *nr24)
{
	uint16_t reg = c1freqtoval(freq);
	*nr23 = reg & 0xff;
	*nr24 = (*nr24 & 0b11111000) | (reg >> 8);
}

static int16_t getc0val()
{
	uint32_t c0freq = c0regtofreq(NR13, NR14);
	if (frame >= c0nextenvstepchange)
	{
		uint8_t envstep = NR12 & 0b00000111;
		if (envstep != 0)
		{
			c0nextenvstepchange = frame + envstep * freq / 64;
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
	if (frame >= c0nextswpstepchange)
	{
		uint8_t swptime = NR10 & 0b01110000;
		if (swptime != 0)
		{
			c0nextswpstepchange = frame + swptime * freq / 128;
			bool goUp = NR10 & 0b00001000;
			uint8_t swpShift = NR12 & 0b00000111;
			if (goUp)
			{
				int32_t newfreq = c0freq + c0freq / pow(2, swpShift);
				if (c0freqtoval(newfreq) > 2047)
					newfreq = 2047;
				c0freq = newfreq;
			}
			else
			{
				int32_t newfreq = c0freq - c0freq / pow(2, swpShift);
				if (newfreq < 0)
					newfreq = 0;
				c0freq = newfreq;
			}
		}
	}
	c0freqtoreg(c0freq, &NR13, &NR14);
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
	uint32_t inter = freq / c0freq;
	uint32_t curr = frame & inter;
	if (curr / (float)inter > dutyper)
		return (SHRT_MAX * envVal);
	else
		return (SHRT_MIN * envVal);
}

static int16_t getc1val()
{
	uint32_t c1freq = c1regtofreq(NR23, NR24);
	if (frame >= c1nextenvstepchange)
	{
		uint8_t envstep = NR22 & 0b00000111;
		if (envstep != 0)
		{
			c0nextenvstepchange = frame + envstep * freq / 64;
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
	c0freqtoreg(c1freq, &NR23, &NR24);
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
	uint32_t inter = freq / c1freq;
	uint32_t curr = frame & inter;
	if (curr / (float)inter > dutyper)
		return (SHRT_MAX * envVal);
	else
		return (SHRT_MIN * envVal);
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
		int16_t c0 = 0;
		if (Main::getAudio()->getMode() & AUDIO_MODE_1)
			c0 = getc0val();
		int16_t c1 = 0;
		if (Main::getAudio()->getMode() & AUDIO_MODE_2)
			c1 = getc1val();
		out[i] = 0;
		out[i] += c0 / 2;
		out[i] += c1 / 2;
		out[i] *= Main::getAudio()->getLevel() / 7.;
		if (i & 0x1)
			++frame;
	}
	//if (frame % 10000 == 0)
	//	Main::getAudio()->getLevel() = (Main::getAudio()->getLevel() + 1) % 8;
	return (paContinue);
}

Audio::Audio()
{
	this->mode = 0xff;
	this->level = 1;
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
