#include "LCD.h"
#include "Main.h"
#include <iostream>

static memboy mem;

static uint32_t getColorForPalette(uint8_t palette, uint8_t color)
{
	uint16_t palettecolor = (uint16_t)mem[OBP0 + (OBP1 - OBP0) * palette + color * 2];
	return ((palettecolor & 0b00011111) | ((palettecolor & 0b0000001111100000) << 3) | ((palettecolor & 0b011111000000000) << 6));
}

void LCD::render()
{
	for (uint8_t y = 0; y < 144; ++y)
	{
		mem[LY] = y;
		mem[STAT] = ((uint8_t)mem[STAT] & 0b11111011) | ((uint8_t)mem[LY] == (uint8_t)mem[LYC] ? 0x4 : 0);
		mem[STAT] = ((uint8_t)mem[STAT] & 0b11111100) | 2;
		//wait 82 cycles

		//block OAM
		renderOBJ(y);
		mem[STAT] = ((uint8_t)mem[STAT] & 0b11111100) | 3;
		//wait 172 cycles

		//block VRAM
		renderBG(y);
		if ((uint8_t)mem[LCDC] & 0b00100000)
			renderWindow(y);
		//release OAM & VRAM
		mem[STAT] = ((uint8_t)mem[STAT] & 0b11111100) | 0;
		//wait 202 cycles
	}
	mem[STAT] = ((uint8_t)mem[STAT] & 0b11111100) | 1;
	for (uint8_t y = 144; y < 154; ++y)
	{
		mem[LY] = y;
		mem[STAT] = ((uint8_t)mem[STAT] & 0b11111011) | ((uint8_t)mem[LY] == (uint8_t)mem[LYC] ? 0x4 : 0);
		//wait 465 cycles
	}
}

static void renderBGCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode)
{
	uint16_t charaddr = (uint8_t)mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN;
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t color = ((uint8_t)mem[charaddr + idx / 8]) >> (idx % 8);
	Main::getMainDisplay()->putPixel(x, y, color | (color << 8) | (color << 16));
}

static void renderBGCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	uint16_t charaddr = (uint8_t)mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN;
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t palette = attr & 0b00000111;
	uint8_t charbank = (attr & 0b00001000) >> 3;
	bool hflip = (attr & 0b00100000) >> 5;
	bool vflip = (attr & 0b01000000) >> 6;
	uint8_t priority = (attr & 0b10000000) >> 7;
	uint8_t coloridx;
	if (charbank)
		coloridx = ((uint8_t)mem.cbank1(charaddr + idx / 8)) >> (idx % 8);
	else
		coloridx = ((uint8_t)mem.cbank0(charaddr + idx / 8)) >> (idx % 8);
	if (hflip)
		bx = 7 - bx;
	if (vflip)
		by = 7 - by;
	uint32_t color = getColorForPalette(palette, coloridx);
	Main::getMainDisplay()->putPixel(x, y, color);
	(void)priority;
	//TODO priority
}

void LCD::renderBG(uint8_t y)
{
	uint16_t baseaddr = (uint8_t)mem[LCDC] & 0b00001000 ? LCD_BG2_BEGIN : LCD_BG1_BEGIN;
	uint8_t scx = mem[SCX];
	uint8_t scy = mem[SCY];
	for (uint8_t x = 0; x < 160; ++x)
	{
		uint8_t rx = scx + x;
		uint8_t ry = scy + y;
		uint8_t bx = rx % 8;
		uint8_t by = ry % 8;
		uint32_t addr = baseaddr + (rx - bx) + (ry - by) * 32;
		uint8_t charcode = mem.cbank0(addr);
		if (true/*DMG*/)
			renderBGCharDMG(x, y, bx, by, charcode);
		else if (true/*CGB*/)
			renderBGCharCGB(x, y, bx, by, charcode, mem.cbank1(addr));
	}
}

void LCD::renderOBJ(uint8_t y)
{
	for (uint8_t i = 0; i < 40; ++i)
	{
		uint32_t addr = LCD_OAM_BEGIN;
		uint8_t y = mem[addr + 0];
		uint8_t x = mem[addr + 1];
		//
		uint8_t charcode = mem[addr + 2];
		uint8_t attr = mem[addr + 3];
		uint8_t colPal = attr & 0x7;  //CGB
		uint8_t charBank = attr & 0x8;//CGB
		uint8_t pal = attr & 0x10; //DMG
		bool hflip = attr & 0x20;
		bool vflip = attr & 0x40;
		uint8_t priority = attr & 0x80;
		//if (true/*DMG*/)
		//	renderOBJChatDMG(x, y, 
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

void LCD::renderWindow(uint8_t y)
{
	//
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
