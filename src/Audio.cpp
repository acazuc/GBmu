#include "Audio.h"
#include "Main.h"
#include <jackshit.h>
#include <iostream>
#include <unistd.h>
#include <climits>
#include <cmath>

#define CLOCK_FREQ 4194304

static uint64_t freq = CLOCK_FREQ / 32;
static uint64_t frame = 0;

static uint64_t c1len = 0;
static uint64_t c2len = 0;
static uint64_t c3len = 0;
static uint64_t c4len = 0;
static uint64_t c1env = 0;
static uint64_t c2env = 0;
static uint64_t c3env = 0;
static uint64_t c4env = 0;
static uint8_t c1envstep = 0;
static uint8_t c2envstep = 0;
static uint8_t c4envstep = 0;
static bool c1envdir = false;
static bool c2envdir = false;
static bool c4envdir = false;
static uint8_t c1swptime = 0;
static bool c1swpdir = false;
static uint8_t c1swpshift = 0;
static uint16_t c1swpfreq = 0;
static uint64_t c1lastswptick = 0;
static uint64_t c1lastenvtick = 0;
static uint64_t c2lastenvtick = 0;
static uint64_t c4lastenvtick = 0;

static uint64_t c4nextclocktick = 0;
static uint16_t c4stepcounter = 0;
static uint16_t c4stepstate = 0xffff;
static float c4divider = 1;

static uint64_t clockCount = 0;
static uint64_t nextClock = 0;
static uint64_t envtick = 0;
static uint64_t swptick = 0;

static uint16_t c1freqtoval(uint32_t freq)
{
	return (2048 - CLOCK_FREQ / (32 * freq));
}

static uint32_t c1valtofreq(int32_t val)
{
	return (CLOCK_FREQ / (32 * (2048 - val)));
}

static uint32_t c1regtofreq(uint8_t nr13, uint8_t nr14)
{
	uint16_t val = (uint16_t)nr13 | (((uint16_t)(nr14 & 0x7)) << 8);
	return (c1valtofreq(val));
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
	if (core::mem.sysregs(NR14) & 0b10000000)
	{
		c1len = 64 - (core::mem.sysregs(NR11) & 0b00111111);
		c1env = (core::mem.sysregs(NR12) & 0b11110000) >> 4;
		c1envdir = core::mem.sysregs(NR12) & 0b00001000;
		c1envstep = core::mem.sysregs(NR12) & 0b00000111;
		c1swpfreq = ((core::mem.sysregs(NR14) & 0b00000111) << 8) | core::mem.sysregs(NR13);
		c1swptime = (core::mem.sysregs(NR10) & 0b01110000) >> 4;
		c1swpdir = core::mem.sysregs(NR10) & 0b00001000;
		c1swpshift = core::mem.sysregs(NR10) & 0b00000111;
		core::mem.sysregs(NR14) &= 0b01111111;
		core::mem.sysregs(NR52) |= 0b00000001;
	}
	if (!c1swpdir && !core::mem.sysregs(NR10) & 8)
	{
		core::mem.sysregs(NR52) &= 0b11111110;
		return (0);
	}
	if (!(core::mem.sysregs(NR12) & 0xF8))
	{
		core::mem.sysregs(NR52) &= 0b11111110;
		return (0);
	}
	uint8_t duty = (core::mem.sysregs(NR11) & 0b11000000) >> 6;
	float dutyper = 0;
	switch (duty)
	{
		case 0b11:
			dutyper = .25;
			break;
		case 0b10:
			dutyper = .5;
			break;
		case 0b01:
			dutyper = .75;
			break;
		case 0b00:
			dutyper = .875;
			break;
	}
	uint32_t c1freq = c1regtofreq(core::mem.sysregs(NR13), core::mem.sysregs(NR14));
	uint32_t inter = freq / c1freq;
	if (!inter)
		return (0);
	uint32_t curr = frame % inter;
	float envfac = c1env / 15.;
	if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SINE)
	{
		float a = curr / (float)inter - dutyper;
		if (a > 0)
			return (SHRT_MAX * sin(a / (1 - dutyper) * M_PI) * envfac);
		return (SHRT_MIN * sin(-a / dutyper * M_PI) * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SAW)
	{
		return ((SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (inter - curr) / (float)inter) * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_TRIANGLE)
	{
		float a = curr / (float)inter - dutyper;
		if (a > 0)
			return ((SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (1 - (a / (1 - dutyper)))) * envfac);
		return ((SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (1 - (-a / dutyper))) * envfac);
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
	if (core::mem.sysregs(NR24) & 0b10000000)
	{
		c2len = 64 - (core::mem.sysregs(NR21) & 0b00111111);
		c2env = (core::mem.sysregs(NR22) & 0b11110000) >> 4;
		c2envdir = core::mem.sysregs(NR22) & 0b00001000;
		c2envstep = core::mem.sysregs(NR22) & 0b00000111;
		core::mem.sysregs(NR24) &= 0b01111111;
		core::mem.sysregs(NR52) |= 0b00000010;
	}
	if (!(core::mem.sysregs(NR22) & 0xF8))
	{
		core::mem.sysregs(NR52) &= 0b11111101;
		return (0);
	}
	uint32_t c2freq = c1regtofreq(core::mem.sysregs(NR23), core::mem.sysregs(NR24));
	uint8_t duty = (core::mem.sysregs(NR21) & 0b11000000) >> 6;
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
	if (!inter)
		return (0);
	uint32_t curr = frame % inter;
	float envfac = c2env / 15.;
	if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SINE)
	{
		float a = curr / (float)inter - dutyper;
		if (a > 0)
			return (SHRT_MAX * sin(a / (1 - dutyper) * M_PI) * envfac);
		return (SHRT_MIN * sin(-a / (dutyper) * M_PI) * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_SAW)
	{
		return ((SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (inter - curr) / (float)inter) * envfac);
	}
	else if (Main::getAudio()->getC12type() == AUDIO_C12_TYPE_TRIANGLE)
	{
		float a = curr / (float)inter - dutyper;
		if (a > 0)
			return ((SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (1 - (a / (1 - dutyper)))) * envfac);
		return ((SHRT_MIN + (SHRT_MAX - SHRT_MIN) * (1 - (-a / dutyper))) * envfac);
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
	if (!(core::mem.sysregs(NR30) & 0b10000000))
	{
		core::mem.sysregs(NR52) &= 0b11111011;
		return (0);
	}
	if (core::mem.sysregs(NR34) & 0b10000000)
	{
		c3len = 256 - core::mem.sysregs(NR31);
		core::mem.sysregs(NR34) &= 0b01111111;
		core::mem.sysregs(NR52) |= 0b00000100;
	}
	uint32_t c3freq = c3regtofreq(core::mem.sysregs(NR33), core::mem.sysregs(NR34));
	uint32_t inter = freq / c3freq;
	if (!inter)
		return (0);
	uint8_t idx = (frame % inter) / (float)inter * 32;
	uint8_t tmp = core::mem.sysregs(0xFF30 + idx / 2);
	if (!(idx & 1))
		tmp = tmp >> 4;
	tmp &= 0xf;
	uint8_t idx1 = (idx + 1) % 32;
	uint8_t tmp1 = core::mem.sysregs(0xFF30 + idx1 / 2);
	if (!(idx1 & 1))
		tmp1 = tmp1 >> 4;
	tmp1 &= 0xf;
	int16_t data = SHRT_MIN + (SHRT_MAX - SHRT_MIN) * tmp / 0xf;
	int16_t data1 = SHRT_MIN + (SHRT_MAX - SHRT_MIN) * tmp1 / 0xf;
	float interpfac = ((frame % inter) / (float)inter * 32) - idx;
	int16_t val = data + (data1 - data) * interpfac;
	uint8_t level = (core::mem.sysregs(NR32) & 0b01100000) >> 5;
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
	if (core::mem.sysregs(NR44) & 0b10000000)
	{
		c4stepstate = 0xff;
		c4stepcounter = 0;
		c4len = 64 - (core::mem.sysregs(NR41) & 0b00111111);
		uint8_t tmp = core::mem.sysregs(NR43) & 0b00000111;
		if (tmp == 0b000)
			c4divider = .5;
		else
			c4divider = tmp;
		c4divider *= pow(2, ((core::mem.sysregs(NR43) & 0b11110000) >> 4) + 1);
		c4nextclocktick = frame + freq / (524288 / c4divider);
		c4env = (core::mem.sysregs(NR42) & 0b11110000) >> 4;
		c4envdir = core::mem.sysregs(NR42) & 0b00001000;
		c4envstep = core::mem.sysregs(NR42) & 0b00000111;
		core::mem.sysregs(NR44) &= 0b01111111;
		core::mem.sysregs(NR52) |= 0b00001000;
	}
	if (!(core::mem.sysregs(NR42) & 0xF8))
	{
		core::mem.sysregs(NR52) &= 0b11110111;
		return (0);
	}
	if (frame >= c4nextclocktick)
	{
		if (c4stepcounter > 32767)
		{
			c4stepcounter = 0;
			c4stepstate = 0xffff;
		}
		uint8_t xored = (c4stepstate & 0x1) ^ ((c4stepstate & 0x2) >> 1);
		c4stepstate >>= 1;
		c4stepstate = (c4stepstate & 0b011111111111111) | (xored << 14);
		if (core::mem.sysregs(NR43) & 0b00001000)
			c4stepstate = (c4stepstate & 0b0111111) | (xored << 6);
		c4nextclocktick = frame + freq / (524288 / c4divider);
		++c4stepcounter;
	}
	float envfac = c4env / 15.;
	if (c4stepstate & 1)
		return (SHRT_MAX * envfac);
	return (SHRT_MIN * envfac);
}

static void updateLengthTick()
{
	//Channel 1
	if (core::mem.sysregs(NR14) & 0b01000000)
	{
		c1len--;
		if (c1len == 0)
			core::mem.sysregs(NR52) &= 0b11111110;
	}
	//Channel 2
	if (core::mem.sysregs(NR24) & 0b01000000)
	{
		c2len--;
		if (c2len == 0)
			core::mem.sysregs(NR52) &= 0b11111101;
	}
	//Channel 3
	if (core::mem.sysregs(NR34) & 0b01000000)
	{
		c3len--;
		if (c3len == 0)
			core::mem.sysregs(NR52) &= 0b11111011;
	}
	//Channel 4
	if (core::mem.sysregs(NR44) & 0b01000000)
	{
		c4len--;
		if (c4len == 0)
			core::mem.sysregs(NR52) &= 0b11110111;
	}
}

static void updateEnvTick()
{
	//Channel 1
	{
		if (c1envstep && envtick - c1lastenvtick >= c1envstep)
		{
			c1lastenvtick = envtick;
			if (c1envdir)
			{
				if (c1env != 0b1111)
					c1env++;
			}
			else
			{
				c1env--;
				if (c1env == 0)
					core::mem.sysregs(NR52) &= 0b11111110;
			}
		}
	}
	//Channel 2
	{
		if (c2envstep && envtick - c2lastenvtick >= c2envstep)
		{
			c2lastenvtick = envtick;
			if (c2envdir)
			{
				if (c2env != 0b1111)
					c2env++;
			}
			else
			{
				c2env--;
				if (c2env == 0)
					core::mem.sysregs(NR52) &= 0b11111101;
			}
		}
	}
	//Channel 4
	{
		if (c4envstep && envtick - c4lastenvtick >= c4envstep)
		{
			c4lastenvtick = envtick;
			if (c4envdir)
			{
				if (c4env != 0b1111)
					c4env++;
			}
			else
			{
				c4env--;
				if (c4env == 0)
					core::mem.sysregs(NR52) &= 0b11110111;
			}
		}
	}
}

static void updateSweepTick()
{
	//Channel 1
	{
		if (c1swptime && c1swpshift && swptick - c1lastswptick >= c1swptime)
		{
			c1lastswptick = swptick;
			if (!c1swpdir)
			{
				c1swpfreq += c1swpfreq >> c1swpshift;
				if (c1swpfreq > 2047)
					core::mem.sysregs(NR52) &= 0b11111110;
				core::mem.sysregs(NR13) = c1swpfreq & 0xff;
				core::mem.sysregs(NR14) = (core::mem.sysregs(NR14) & 0b11111000) | (c1swpfreq >> 8);
			}
			else
			{
				c1swpfreq -= (c1swpfreq >> c1swpshift);
				core::mem.sysregs(NR13) = c1swpfreq & 0xff;
				core::mem.sysregs(NR14) = (core::mem.sysregs(NR14) & 0b11111000) | (c1swpfreq >> 8);
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
		if (Main::isPaused())
			continue;
		if (core::mem.sysregs(NR52) & 0b10000000)
		{
			bool c1on = core::mem.sysregs(NR52) & 0b00000001;
			bool c2on = core::mem.sysregs(NR52) & 0b00000010;
			bool c3on = core::mem.sysregs(NR52) & 0b00000100;
			bool c4on = core::mem.sysregs(NR52) & 0b00001000;
			int16_t c1 = getc1val() & 0xf000;
			int16_t c2 = getc2val() & 0xf000;
			int16_t c3 = getc3val() & 0xf000;
			int16_t c4 = getc4val() & 0xf000;
			uint8_t pcm12 = 0;
			if (c1on)
				pcm12 += ((c1 >> 12) - CHAR_MIN);
			if (c2on)
				pcm12 += ((c2 >> 12) - CHAR_MIN) << 4;
			core::mem.sysregs(PCM12) = pcm12;
			uint8_t pcm34 = 0;
			if (c3on)
				pcm34 += ((c3 >> 12) - CHAR_MIN);
			if (c4on)
				pcm34 += ((c4 >> 12) - CHAR_MIN) << 4;
			core::mem.sysregs(PCM34) = pcm34;
			if (i & 0x1)
			{
				bool lc1on = c1on && (core::mem.sysregs(NR51) & 0b00000001);
				bool lc2on = c2on && (core::mem.sysregs(NR51) & 0b00000010);
				bool lc3on = c3on && (core::mem.sysregs(NR51) & 0b00000100);
				bool lc4on = c4on && (core::mem.sysregs(NR51) & 0b00001000);
				if (lc1on)
					out[i] += c1 / 4.;
				if (lc2on)
					out[i] += c2 / 4.;
				if (lc3on)
					out[i] += c3 / 4.;
				if (lc4on)
					out[i] += c4 / 4.;
				out[i] *= ((core::mem.sysregs(NR50) & 0b00000111) >> 0) / 7.;
			}
			else
			{
				bool rc1on = c1on && (core::mem.sysregs(NR51) & 0b00010000);
				bool rc2on = c2on && (core::mem.sysregs(NR51) & 0b00100000);
				bool rc3on = c3on && (core::mem.sysregs(NR51) & 0b01000000);
				bool rc4on = c4on && (core::mem.sysregs(NR51) & 0b10000000);
				if (rc1on)
					out[i] += c1 / 4.;
				if (rc2on)
					out[i] += c2 / 4.;
				if (rc3on)
					out[i] += c3 / 4.;
				if (rc4on)
					out[i] += c4 / 4.;
				out[i] *= ((core::mem.sysregs(NR50) & 0b01110000) >> 4) / 7.;
			}
		}
		if (frame >= nextClock)
		{
			if (clockCount % 1 == 1)
			{
				updateLengthTick();
			}
			if (clockCount % 8 == 7)
			{
				updateEnvTick();
				envtick++;
			}
			if (clockCount % 4 == 2)
			{
				updateSweepTick();
				swptick++;
			}
			clockCount++;
			nextClock += freq / 512;
		}
		if (i & 0x1)
			++frame;
		if (Main::getAudio()->isMute())
			out[i] = 0;
	}
	return (paContinue);
}

Audio::Audio()
: c12type(AUDIO_C12_TYPE_SQUARE)
, mute(false)
{
	PaStreamParameters parameters;
	parameters.device = Pa_GetDefaultOutputDevice();
	const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(parameters.device);
	parameters.channelCount = 2;
	parameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
	parameters.sampleFormat = paInt16;
	parameters.hostApiSpecificStreamInfo = 0;
	PaError error = Pa_OpenStream(&this->stream, 0, &parameters, freq, freq / 128, paNoFlag, paCallback, this);
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
