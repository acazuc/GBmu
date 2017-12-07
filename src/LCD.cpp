#include "LCD.h"
#include "Main.h"
#include <iostream>

static memboy mem;

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

void LCD::renderBGCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode)
{
	uint16_t charaddr = (uint8_t)mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN;
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t color = ((uint8_t)mem[charaddr + idx / 8]) >> (idx % 8);
	uint32_t col = color | (color << 8) | (color << 16) | (color << 24);
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&col);
}

void LCD::renderBGCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
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
	Main::getMainDisplay()->putPixel(x, y, bgpalettes[palette][coloridx]);
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

void LCD::CPSCallback(uint8_t addr, uint8_t value)
{
	uint8_t hl = value & 0b00000001;
	uint8_t colorid = (value & 0b00000110) >> 1;
	uint8_t paletteid = (value & 0b00111000) >> 3;
	uint8_t *palette = addr == BCPS ? bgpalettes[paletteid][colorid] : objpalettes[paletteid][colorid];
	uint8_t color;
	if (hl)
	{
		uint8_t blue = (palette[2] & 0b00011111) << 2;
		uint8_t green = (palette[1] & 0b00011000) >> 3;
		color = blue | green;
	}
	else
	{
		uint8_t green = (palette[1] & 0b00000111) << 5;
		uint8_t red = (palette[0] & 0b00011111);
		color = green | red;
	}
	mem[addr = BCPS ? BCPD : OCPD] = color;
}

void LCD::CPDCallback(uint8_t addr, uint8_t value)
{
	uint8_t CPS = (uint8_t)mem[addr == BCPD ? BCPS : OCPS];
	uint8_t hl = CPS & 0b00000001;
	uint8_t colorid = (CPS & 0b00000110) >> 1;
	uint8_t paletteid = (CPS & 0b00111000) >> 3;
	uint8_t inc = (CPS & 0b10000000) >> 7;
	uint8_t *palette = addr == BCPD ? bgpalettes[paletteid][colorid] : objpalettes[paletteid][colorid];
	if (inc)
	{
		uint8_t val = (CPS & 0x80) | (((CPS & 0x3F) + 1) & 0x3F);
		mem[addr = BCPD ? BCPS : OCPS] = val;
		CPSCallback(addr = BCPD ? BCPS : OCPS, val);
	}
	if (hl)
	{
		uint8_t blue = (value & 0b01111100) >> 2;
		uint8_t green = (value & 0b00000011);
		palette[1] = (palette[1] & 0b00000111) | (green << 3);
		palette[2] = blue;
	}
	else
	{
		uint8_t green = (value & 0b11100000) >> 5;
		uint8_t red = (value & 0b00011111);
		palette[1] = (palette[1] & 0b00011000) | green;
		palette[2] = red;
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
