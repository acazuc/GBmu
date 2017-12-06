#include "LCD.h"
#include "Main.h"
#include <iostream>

static memboy mem;

void LCD::render()
{
	for (uint8_t y = 0; y < 144; ++y)
	{
		mem[STAT] = ((uint8_t)mem[STAT] & 0xfc) | 2;
		//wait 82 cycles

		//block OAM
		renderOBJ(y);
		mem[STAT] = ((uint8_t)mem[STAT] & 0xfc) | 3;
		//wait 172 cycles

		//block VRAM
		renderBG(y);
		//release OAM & VRAM
		mem[STAT] = ((uint8_t)mem[STAT] & 0xfc) | 0;
		//wait 202 cycles
	}
	mem[STAT] = ((uint8_t)mem[STAT] & 0xfc) | 1;
	//wait 4650 cycles
}

void LCD::renderBG(uint8_t y)
{
	uint32_t baseMem = (uint8_t)mem[LCDC] & 0x8 ? LCD_BG2_BEGIN : LCD_BG1_BEGIN;
	uint8_t scx = mem[SCX];
	uint8_t scy = mem[SCY];
	for (uint8_t x = 0; x < 20; ++x)
	{
		uint32_t trueX = (scx + x) % 32;
		uint32_t trueY = (scy + y) % 32;
		uint32_t addr = baseMem + trueX + trueY * 32;
		uint8_t charcode = mem.cbank0(addr);
		bool hflip = false;
		bool vflip = false;
		if (true/*CGB*/)
		{
			uint8_t attr = mem.cbank1(addr);
			uint8_t colPal = attr & 0x7;
			uint8_t charBank = attr & 0x8;
			hflip = attr & 0x20;
			vflip = attr & 0x40;
			uint8_t priority = attr & 0x80;
			(void)colPal;
			(void)charBank;
			(void)priority;
		}
		printChar(x * 8, y * 8, charcode, hflip, vflip);
	}
}

void LCD::renderOBJ(uint8_t y)
{
	for (uint8_t i = 0; i < 40; ++i)
	{
		uint32_t addr = LCD_OAM_BEGIN;
		uint8_t y = mem[addr + 0];
		uint8_t x = mem[addr + 1];
		uint8_t charcode = mem[addr + 2];
		uint8_t attr = mem[addr + 3];
		uint8_t colPal = attr & 0x7;  //CGB-only
		uint8_t charBank = attr & 0x8;//CGB-only
		uint8_t pal = attr & 0x10; //DMG / DMG-mode
		bool hflip = attr & 0x20;
		bool vflip = attr & 0x40;
		uint8_t priority = attr & 0x80;
		//printChar(x * 8, y * 8, charcode, hflip, vflip);
		(void)x;
		(void)y;
		(void)colPal;
		(void)charBank;
		(void)pal;
		(void)hflip;
		(void)vflip;
		(void)priority;
	}
}

static uint8_t datas[] =
{
	3, 3, 2, 0, 0, 2, 3, 3,
	3, 3, 1, 0, 0, 1, 3, 3,
	3, 3, 0, 1, 1, 0, 3, 3,
	3, 2, 0, 2, 2, 0, 2, 3,
	3, 1, 0, 0, 0, 0, 1, 3,
	3, 0, 1, 2, 2, 1, 0, 3,
	2, 0, 2, 3, 3, 2, 0, 2,
	1, 0, 3, 3, 3, 3, 0, 1,
};

void LCD::printChar(uint8_t cx, uint8_t cy, uint8_t charcode, bool hflip, bool vflip)
{
	uint32_t addr = uint8_t(mem[LCDC]) & 0x16 ? LCD_CHAR2_BEGIN : LCD_CHAR1_BEGIN;
	for (uint8_t x = 0; x < 8; ++x)
	{
		for (uint8_t y = 0; y < 8; ++y)
		{
			uint8_t xx = x;
			if (hflip)
				xx = 7 - x;
			uint8_t yy = y;
			if (vflip)
				yy = 7 - y;
			uint8_t idx = yy * 8 + xx;
			//uint8_t color = mem[addr + idx / 4] & (3 << (idx % 4));
			uint8_t color = datas[idx] / 3. * UCHAR_MAX;
			for (uint8_t i = 0; i < 3; ++i)
				Main::getMainDisplay()->getTexDatas()[((cy + y) * 160 + cx + x) * 3 + i] = color;
			(void)color;
			(void)charcode;
		}
	}
}
