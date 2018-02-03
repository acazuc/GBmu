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
	core::mem[BGP] = 0xFC;
}

void LCD::render()
{
	bool stopped = core::getstate() == CPU_STOP;
	if (stopped)
		memset(Main::getMainDisplay()->getTexDatas(), 0xff, 160 * 144 * 3);
	bool paused = Main::isPaused();
	uint8_t keys = 0xF;
	if (!(core::mem[JOYP] & 0b00010000))
	{
		if (Main::getMainDisplay()->getKeys() & 0b00000001)
			keys &= ~0b00000010;
		if (Main::getMainDisplay()->getKeys() & 0b00000010)
			keys &= ~0b00000001;
		if (Main::getMainDisplay()->getKeys() & 0b00000100)
			keys &= ~0b00000100;
		if (Main::getMainDisplay()->getKeys() & 0b00001000)
			keys &= ~0b00001000;
	}
	if (!(core::mem[JOYP] & 0b00010000))
	{
		if (Main::getMainDisplay()->getKeys() & 0b00010000)
			keys &= ~0b00000100;
		if (Main::getMainDisplay()->getKeys() & 0b00100000)
			keys &= ~0b00001000;
		if (Main::getMainDisplay()->getKeys() & 0b01000000)
			keys &= ~0b00000010;
		if (Main::getMainDisplay()->getKeys() & 0b10000000)
			keys &= ~0b00000001;
	}
	core::mem[JOYP] = (core::mem[JOYP] & (0b00110000)) | keys;
	if (keys != 0xf)
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
		if (!stopped)
			;//renderOBJ(y);
		core::mem[STAT] = (core::mem[STAT] & 0b11111100) | 3;
		if (core::mem[STAT] & 0b00001000)
			core::mem[IF] |= 1 << 1;
		if (!paused)
			corerun(172 / div);
		if (!stopped)
			renderBG(y);
		//if (core::mem[LCDC] & 0b00100000)
		//	renderWindow(y);
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
	uint16_t charaddr = core::mem[LCDC] & 0b00010000 ? LCD_BG1_CHAR_BEGIN : LCD_BG2_CHAR_BEGIN;
	charaddr += charcode * 16;
	uint8_t color = ((core::mem[charaddr + by * 2]) >> (7 - bx)) & 1;
	color = (color << 1) | ((core::mem[charaddr + by * 2 + 1] >> (7 - bx)) & 1);
	color = (core::mem[BGP] >> (color * 2)) & 0x3;
	color = UCHAR_MAX - (color / 3. * UCHAR_MAX);
	uint8_t col[] = {color, color, color, color};
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&col);
	priorities[y][x] = 0;
	hasprinted[y][x] = col != 0;
}

void LCD::renderBGCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	uint16_t charaddr = core::mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN;
	uint16_t idx = (bx + by * 8) * 2;
	uint8_t palette = attr & 0b00000111;
	uint8_t charbank = (attr & 0b00001000) >> 3;
	bool hflip = (attr & 0b00100000) >> 5;
	bool vflip = (attr & 0b01000000) >> 6;
	uint8_t priority = (attr & 0b10000000) >> 7;
	uint8_t coloridx;
	if (charbank)
		coloridx = (core::mem.cbank1(charaddr + idx / 8)) >> (idx % 8);
	else
		coloridx = (core::mem.cbank0(charaddr + idx / 8)) >> (idx % 8);
	coloridx %= 4;
	if (hflip)
		bx = 7 - bx;
	if (vflip)
		by = 7 - by;
	Main::getMainDisplay()->putPixel(x, y, bgpalettes[palette][coloridx]);
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
	uint16_t charaddr = 0x8000 + ((charcode & 0b11111110) >> 1) * (height16 ? 32 : 16);
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t pixel = ((core::mem[charaddr + by * 2]) >> (7 - bx)) & 1;
	pixel = (pixel << 1) | (((core::mem[charaddr + by * 2 + 1]) >> (7 - bx)) & 1);
	pixel = UCHAR_MAX - (pixel / 3. * UCHAR_MAX);
	uint8_t color = ((core::mem[palette ? OBP0 : OBP1] >> (pixel * 2)) & 0b00000011) / 3. * UCHAR_MAX;
	if (priorities[y][x])
	{
		if (hasprinted[y][x] || !color)
			return;
	}
	else
	{
		if (priority)
		{
			if (hasprinted[y][x] || !color)
				return;
		}
		else
		{
			if (!color)
				return;
		}
	}
	uint8_t col[] = {color, color, color, color};
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&color);
}

void LCD::renderOBJCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	bool height16 = core::mem[LCDC] & 0b00000100;
	uint8_t palette = attr & 0b00000111;
	uint8_t charbank = (attr & 0b00001000) >> 3;
	bool hflip = (attr & 0b00100000) >> 5;
	bool vflip = (attr & 0b01000000) >> 6;
	uint8_t priority = (attr & 0b10000000) >> 7;
	if (hflip)
		bx = 7 - bx;
	if (vflip)
		by = (height16 ? 15 : 7) - by;
	uint16_t charaddr = 0x8000 + ((charcode & 0b11111110) >> 1) * (height16 ? 32 : 16);
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t pixel;
	if (charbank)
		pixel = ((core::mem.cbank1(charaddr + idx / 8)) >> (idx % 8)) & 0b00000111;
	else
		pixel = ((core::mem.cbank0(charaddr + idx / 8)) >> (idx % 8)) & 0b00000111;
	uint8_t *color = objpalettes[palette][pixel];
	if (priorities[y][x])
	{
		if (hasprinted[y][x] || !color)
			return;
	}
	else
	{
		if (priority)
		{
			if (hasprinted[y][x] || !color)
				return;
		}
		else
		{
			if (!color)
				return;
		}
	}
	Main::getMainDisplay()->putPixel(x, y, color);
}

void LCD::renderOBJ(uint8_t y)
{
	bool height16 = core::mem[LCDC] & 0b00000100;
	uint8_t spritescount = 0;
	uint8_t lowestx[160];
	std::memset(lowestx, 0xff, 160);
	for (uint8_t i = 39; i >= 0; --i)
	{
		uint32_t addr = LCD_OAM_BEGIN + 4 * i;
		uint8_t cy = core::mem[addr + 0];
		if (cy > y || cy + (height16 ? 16 : 8) <= y)
			continue;
		uint8_t cx = core::mem[addr + 1];
		if (cx < -7 || cx >= 160)
			continue;
		uint8_t charcode = core::mem[addr + 2];
		uint8_t attr = core::mem[addr + 3];
		for (uint8_t x = 0; x < 8; ++x)
		{
			if (cx + x >= 160)
				return;
			if (true/*DMG*/ && cx > lowestx[cx + x])
				continue;
			lowestx[cx + x] = cx;
			if (true/*DMG*/)
				renderOBJCharDMG(cx + x, y, x, y - cy, charcode, attr);
			else /*CGB*/
				renderOBJCharCGB(cx + x, y, x, y - cy, charcode, attr);
		}
		if (++spritescount >= 10)
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
		uint32_t addr = baseaddr + (rx - bx) + (ry - by) * 32;
		uint8_t charcode = core::mem.cbank0(addr);
		if (true/*DMG*/)
			renderBGCharDMG(x, y, bx, by, charcode);
		else/*CGB*/
			renderBGCharCGB(x, y, bx, by, charcode, core::mem.cbank1(addr));
	}
}

void LCD::CPSCallback(uint16_t addr, uint8_t value)
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
	core::mem[addr == BCPS ? BCPD : OCPD] = color;
}

void LCD::CPDCallback(uint16_t addr, uint8_t value)
{
	uint8_t CPS = core::mem[addr == BCPD ? BCPS : OCPS];
	uint8_t hl = CPS & 0b00000001;
	uint8_t colorid = (CPS & 0b00000110) >> 1;
	uint8_t paletteid = (CPS & 0b00111000) >> 3;
	uint8_t inc = (CPS & 0b10000000) >> 7;
	uint8_t *palette = addr == BCPD ? bgpalettes[paletteid][colorid] : objpalettes[paletteid][colorid];
	if (inc)
	{
		uint8_t val = (CPS & 0x80) | (((CPS & 0x3F) + 1) & 0x3F);
		core::mem[addr == BCPD ? BCPS : OCPS] = val;
		CPSCallback(addr == BCPD ? BCPS : OCPS, val);
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
