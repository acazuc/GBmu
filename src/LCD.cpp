#include "LCD.h"
#include "Main.h"
#include <jackshit.h>
#include <cstring>
#include <chrono>
#include <cmath>

using namespace chrono;

LCD::LCD()
{
	std::memset(objpalettes, 0, sizeof(objpalettes));
	std::memset(bgpalettes, 0, sizeof(bgpalettes));
}

void LCD::render()
{
	bool stopped = core::getstate() == CPU_STOP;
	if (stopped)
		memset(Main::getMainDisplay()->getTexDatas(), 0xff, 160 * 144 * 3);
	bool paused = Main::isPaused();
	uint8_t keys_org = core::mem[JOYP] & 0xf;
	uint8_t keys = 0xf;
	uint8_t arrowsstate = 0xF;
	if (Main::getMainDisplay()->getKeys() & 0b00000001)
		arrowsstate &= ~0b00000010;
	if (Main::getMainDisplay()->getKeys() & 0b00000010)
		arrowsstate &= ~0b00000001;
	if (Main::getMainDisplay()->getKeys() & 0b00000100)
		arrowsstate &= ~0b00000100;
	if (Main::getMainDisplay()->getKeys() & 0b00001000)
		arrowsstate &= ~0b00001000;
	if (!(core::mem[JOYP] & 0b00010000))
		keys &= ~arrowsstate;
	core::mem.setarrowsstate(arrowsstate);
	uint8_t buttonsstate = 0xf;
	if (Main::getMainDisplay()->getKeys() & 0b00010000)
		buttonsstate &= ~0b00000100;
	if (Main::getMainDisplay()->getKeys() & 0b00100000)
		buttonsstate &= ~0b00001000;
	if (Main::getMainDisplay()->getKeys() & 0b01000000)
		buttonsstate &= ~0b00000010;
	if (Main::getMainDisplay()->getKeys() & 0b10000000)
		buttonsstate &= ~0b00000001;
	if (!(core::mem[JOYP] & 0b00100000))
		keys &= ~buttonsstate;
	core::mem.setbuttonsstate(buttonsstate);
	if (keys != keys_org)
		core::mem[IF] |= 1 << 4;
	uint8_t div = core::is2xspeed() ? 2 : 4;
	for (uint8_t y = 0; y < 144; ++y)
	{
		std::memset(priorities[y], 0, sizeof(priorities[y]));
		std::memset(hasprinted[y], 0, sizeof(hasprinted[y]));
		core::mem[LY] = y;
		if (core::mem[LCDC] & 0b10000000 && core::mem[LY] == core::mem[LYC])
			core::mem[IF] |= 1 << 1;
		core::mem[STAT] = (core::mem[STAT] & 0b11111011) | (core::mem[LY] == core::mem[LYC] ? 0x4 : 0);
		core::mem[STAT] = (core::mem[STAT] & 0b11111100) | 2;
		if (core::mem[STAT] & 0b00100000)
			core::mem[IF] |= 1 << 1;
		if (!paused)
			corerun(80 / div);
		core::mem[STAT] = (core::mem[STAT] & 0b11111100) | 3;
		if (core::mem[STAT] & 0b00001000)
			core::mem[IF] |= 1 << 1;
		if (!paused)
			corerun(172 / div);
		if (!stopped && core::mem[LCDC] & 0b00000001)
			renderBG(y);
		if (!stopped && core::mem[LCDC] & 0b00100000)
			renderWindow(y);
		if (/*!core::mem.isdmalocked() && */!stopped && core::mem[LCDC] & 0b00000010)
			renderOBJ(y);
		core::mem[STAT] = (core::mem[STAT] & 0b11111100) | 0;
		if (core::mem[STAT] & 0b00010000)
			core::mem[IF] |= 1 << 1;
		if (!paused)
			corerun(204 / div);
	}
	core::mem[STAT] = (core::mem[STAT] & 0b11111100) | 1;
	for (uint8_t y = 144; y < 154; ++y)
	{
		core::mem[LY] = y;
		core::mem[STAT] = (core::mem[STAT] & 0b11111011) | (core::mem[LY] == core::mem[LYC] ? 0b00000100 : 0);
		if (y == 144)
			core::mem[IF] |= 1 << 0;
		if (core::mem[STAT] & 0b10000000 && core::mem[LY] == core::mem[LYC])
			core::mem[IF] |= 1 << 1;
		if (core::mem[STAT] & 0b00100000)
			core::mem[IF] |= 1 << 1;
		if (!paused)
			corerun(456 / div);
	}
}

void LCD::renderBGCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode)
{
	uint16_t charaddr = charcode * 16 + (core::mem[LCDC] & 0b00010000 ? LCD_BG1_CHAR_BEGIN : LCD_BG2_CHAR_BEGIN);
	uint8_t color = (core::mem[charaddr + by * 2] >> ((~bx) & 7)) & 1;
	color = (color << 1) | ((core::mem[charaddr + by * 2 + 1] >> ((~bx) & 7)) & 1);
	color = (core::mem[BGP] >> (color << 1)) & 3;
	color = UCHAR_MAX - (color / 3. * UCHAR_MAX);
	uint8_t col[] = {color, color, color};
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&col);
	priorities[y][x] = 0;
	hasprinted[y][x] = col != 0;
}

void LCD::renderBGCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	uint16_t charaddr = charcode * 16 + (core::mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN);
	uint8_t palette = attr & 0b00000111;
	uint8_t charbank = (attr & 0b00001000) >> 3;
	bool hflip = (attr & 0b00100000) >> 5;
	bool vflip = (attr & 0b01000000) >> 6;
	uint8_t priority = (attr & 0b10000000) >> 7;
	uint8_t coloridx;
	if (hflip)
		bx = 7 - bx;
	if (vflip)
		by = 7 - by;
	if (charbank)
	{
		coloridx = core::mem.cbank1(charaddr + by * 2) >> ((~bx) & 7) & 1;
		coloridx |= (core::mem.cbank1(charaddr + by * 2 + 1) >> ((~bx) & 7) & 1) << 1;
	}
	else
	{
		coloridx = core::mem.cbank0(charaddr + by * 2) >> ((~bx) & 7) & 1;
		coloridx |= (core::mem.cbank0(charaddr + by * 2 + 1) >> ((~bx) & 7) & 1) << 1;
	}
	uint8_t *pal = &core::mem.bgpalette(palette)[coloridx * 2];
	uint8_t color[] = {pal[1] & 0b00011111, (pal[1] >> 5) | ((pal[0] << 3) & 0b00011000), (pal[0] >> 2) & 0b00011111};
	Main::getMainDisplay()->putPixel(x, y, color);
	priorities[y][x] = priority;
	hasprinted[y][x] = bgpalettes[palette][coloridx] != 0;
}

void LCD::renderBG(uint8_t y)
{
	uint16_t baseaddr = core::mem[LCDC] & 0b00001000 ? LCD_BG2_BEGIN : LCD_BG1_BEGIN;
	uint8_t scx = core::mem[SCX];
	uint8_t scy = core::mem[SCY];
	for (uint8_t x = 0; x < 160; ++x)
	{
		uint8_t rx = scx + x;
		uint8_t ry = scy + y;
		uint8_t bx = rx % 8;
		uint8_t by = ry % 8;
		uint32_t addr = baseaddr + ((rx - bx) + (ry - by) * 32) / 8;
		uint8_t charcode = core::mem.cbank0(addr);
		if (true/*DMG*/)
			renderBGCharDMG(x, y, bx, by, charcode);
		else/*CGB*/
			renderBGCharCGB(x, y, bx, by, charcode, core::mem.cbank1(addr));
	}
}

void LCD::renderOBJCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	bool height16 = core::mem[LCDC] & 0b00000100;
	uint8_t palette = (attr & 0b00010000) >> 4;
	bool hflip = (attr & 0b00100000) >> 5;
	bool vflip = (attr & 0b01000000) >> 6;
	uint8_t priority = (attr & 0b10000000) >> 7;
	if (hflip)
		bx = 7 - bx;
	if (vflip)
		by = (height16 ? 15 : 7) - by;
	uint16_t charaddr = LCD_OBJ_CHAR_BEGIN + charcode * 16;
	if (height16)
		charaddr &= ~1;
	uint8_t pixel = (core::mem[charaddr + by * 2] >> ((~bx) & 7)) & 1;
	pixel |= ((core::mem[charaddr + by * 2 + 1] >> ((~bx) & 7)) & 1) << 1;
	if (!pixel)
		return;
	if (priorities[y][x] || priority)
	{
		if (hasprinted[y][x])
			return;
	}
	uint8_t color = (core::mem[palette ? OBP1 : OBP0] >> (pixel << 1)) & 3;
	color = UCHAR_MAX - (color / 3. * UCHAR_MAX);
	uint8_t col[] = {color, color, color};
	Main::getMainDisplay()->putPixel(x, y, col);
}

void LCD::renderOBJCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	bool height16 = core::mem[LCDC] & 0b00000100;
	uint8_t palette = attr & 0b00000111;
	bool charbank = (attr & 0b00001000) >> 3;
	bool hflip = (attr & 0b00100000) >> 5;
	bool vflip = (attr & 0b01000000) >> 6;
	uint8_t priority = (attr & 0b10000000) >> 7;
	if (hflip)
		bx = 7 - bx;
	if (vflip)
		by = (height16 ? 15 : 7) - by;
	uint16_t charaddr = LCD_OBJ_CHAR_BEGIN + charcode * 16;
	if (height16)
		charaddr &= ~1;
	uint8_t pixel;
	if (charbank)
	{
		pixel = ((core::mem.cbank1(charaddr + by * 2)) >> ((~bx) & 7)) & 1;
		pixel |= (((core::mem.cbank1(charaddr + by * 2)) >> ((~bx) & 7)) & 1) << 1;
	}
	else
	{
		pixel = ((core::mem.cbank0(charaddr + by * 2)) >> ((~bx) & 7)) & 1;
		pixel |= (((core::mem.cbank0(charaddr + by * 2)) >> ((~bx) & 7)) & 1) << 1;
	}
	if (!pixel)
		return;
	if (priorities[y][x] || priority)
	{
		if (hasprinted[y][x])
			return;
	}
	uint8_t *pal = &core::mem.bgpalette(palette)[pixel * 2];
	uint8_t color[] = {pal[1] & 0b00011111, (pal[1] >> 5) | ((pal[0] << 3) & 0b00011000), (pal[0] >> 2) & 0b00011111};
	Main::getMainDisplay()->putPixel(x, y, color);
}

void LCD::renderOBJ(uint8_t y)
{
	bool height16 = core::mem[LCDC] & 0b00000100;
	uint8_t spritescount = 0;
	uint8_t lowestx[160];
	std::memset(lowestx, 0xff, 160);
	for (int8_t i = 39; i >= 0; --i)
	{
		uint32_t addr = LCD_OAM_BEGIN + 4 * i;
		uint8_t cy = core::mem[addr + 0];
		if (cy == 0 || cy >= 160 || cy > y + 16 || cy + (height16 ? 16 : 8) <= y + 16)
			continue;
		uint8_t cx = core::mem[addr + 1];
		if (cx == 0 || cx >= 168)
			continue;
		uint8_t charcode = core::mem[addr + 2];
		uint8_t attr = core::mem[addr + 3];
		for (uint8_t x = 0; x < 8; ++x)
		{
			if (cx + x < 8 || cx + x >= 168)
				return;
			if (true/*DMG*/ && cx > lowestx[cx + x - 8])
				continue;
			lowestx[cx + x - 8] = cx;
			if (true/*DMG*/)
				renderOBJCharDMG(cx + x - 8, y, x, y - cy + 16, charcode, attr);
			else /*CGB*/
				renderOBJCharCGB(cx + x - 8, y, x, y - cy + 16, charcode, attr);
		}
		if (++spritescount == 10)
			return;
	}
}

void LCD::renderWindow(uint8_t y)
{
	uint16_t baseaddr = core::mem[LCDC] & 0b01000000 ? LCD_BG2_BEGIN : LCD_BG1_BEGIN;
	uint8_t wx = core::mem[WX] - 7;
	uint8_t wy = core::mem[WY];
	if (wx >= 144 || wy > y)
		return;
	for (uint8_t x = 0; x < 160; ++x)
	{
		uint8_t rx = wx + x;
		uint8_t ry = wy + y;
		uint8_t bx = rx % 8;
		uint8_t by = ry % 8;
		uint32_t addr = baseaddr + ((rx - bx) + (ry - by) * 32) / 8;
		uint8_t charcode = core::mem.cbank0(addr);
		if (true/*DMG*/)
			renderBGCharDMG(x, y, bx, by, charcode);
		else/*CGB*/
			renderBGCharCGB(x, y, bx, by, charcode, core::mem.cbank1(addr));
	}
}
