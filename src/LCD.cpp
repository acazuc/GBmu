#include "LCD.h"
#include "Main.h"
#include <cstring>

static memboy mem;

LCD::LCD()
{
	std::memset(objpalettes, 0, sizeof(objpalettes));
	std::memset(bgpalettes, 0, sizeof(bgpalettes));
}

void LCD::render()
{
	for (uint8_t y = 0; y < 144; ++y)
	{
		std::memset(priorities[y], 0, sizeof(priorities[y]));
		std::memset(hasprinted[y], 0, sizeof(hasprinted[y]));
		mem[LY] = y;
		mem[STAT] = (uint8_t)(((uint8_t)mem[STAT] & 0b11111011) | ((uint8_t)mem[LY] == (uint8_t)mem[LYC] ? 0x4 : 0));
		mem[STAT] = (uint8_t)(((uint8_t)mem[STAT] & 0b11111100) | 2);
		//wait 80 cycles

		//block OAM
		renderOBJ(y);
		mem[STAT] = (uint8_t)(((uint8_t)mem[STAT] & 0b11111100) | 3);
		//wait 172 cycles

		//block VRAM
		renderBG(y);
		if ((uint8_t)mem[LCDC] & 0b00100000)
			renderWindow(y);
		//release OAM & VRAM
		mem[STAT] = (uint8_t)(((uint8_t)mem[STAT] & 0b11111100) | 0);
		//wait 204 cycles
	}
	mem[STAT] = (uint8_t)(((uint8_t)mem[STAT] & 0b11111100) | 1);
	for (uint8_t y = 144; y < 154; ++y)
	{
		mem[LY] = y;
		mem[STAT] = (uint8_t)(((uint8_t)mem[STAT] & 0b11111011) | ((uint8_t)mem[LY] == (uint8_t)mem[LYC] ? 0x4 : 0));
		//wait 465 cycles
	}
}

void LCD::renderBGCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode)
{
	uint16_t charaddr = (uint8_t)mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN;
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t color = (((uint8_t)mem[charaddr + idx / 8]) >> (idx % 8)) / 3. * UCHAR_MAX;
	uint32_t col = color | (color << 8) | (color << 16) | (color << 24);
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&col);
	priorities[y][x] = 0;
	hasprinted[y][x] = col != 0;
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
	priorities[y][x] = priority;
	hasprinted[y][x] = bgpalettes[palette][coloridx] != 0;
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
		else/*CGB*/
			renderBGCharCGB(x, y, bx, by, charcode, mem.cbank1(addr));
	}
}

void LCD::renderOBJCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	bool height16 = LCDC & 0b00000100;
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
	uint8_t pixel = (((uint8_t)mem[charaddr + idx / 8]) >> (idx % 8)) & 0b00000111;
	uint8_t color = (((uint8_t)mem[palette ? OBP0 : OBP1] >> (pixel * 2)) & 0b00000011) / 3. * UCHAR_MAX;
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
	uint32_t col = color | (color << 8) | (color << 16) | (color << 24);
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&color);
}

void LCD::renderOBJCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode, uint8_t attr)
{
	bool height16 = LCDC & 0b00000100;
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
		pixel = (((uint8_t)mem.cbank1(charaddr + idx / 8)) >> (idx % 8)) & 0b00000111;
	else
		pixel = (((uint8_t)mem.cbank0(charaddr + idx / 8)) >> (idx % 8)) & 0b00000111;
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
	bool height16 = LCDC & 0b00000100;
	uint8_t spritescount = 0;
	uint8_t lowestx[160];
	std::memset(lowestx, 0xff, 160);
	for (uint8_t i = 39; i >= 0; ++i)
	{
		uint32_t addr = LCD_OAM_BEGIN + 4 * i;
		uint8_t cy = mem[addr + 0];
		if (cy > y || cy + (height16 ? 16 : 8) <= y)
			continue;
		uint8_t cx = mem[addr + 1];
		if (cx < -7 || cx >= 160)
			continue;
		uint8_t charcode = mem[addr + 2];
		uint8_t attr = mem[addr + 3];
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

/*void LCD::renderWindowCharDMG(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode)
{
	uint16_t charaddr = (uint8_t)mem[LCDC] & 0b00010000 ? LCD_BG2_CHAR_BEGIN : LCD_BG1_CHAR_BEGIN;
	uint8_t idx = (bx + by * 8) * 2;
	uint8_t color = (((uint8_t)mem[charaddr + idx / 8]) >> (idx % 8)) / 3. * UCHAR_MAX;
	uint32_t col = color | (color << 8) | (color << 16) | (color << 24);
	Main::getMainDisplay()->putPixel(x, y, (uint8_t*)&col);
	//priorities[y][x] = priority;
	hasprinted[y][x] |= col != 0;
}

void LCD::renderWindowCharCGB(uint8_t x, uint8_t y, uint8_t bx, uint8_t by, uint8_t charcode)
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
	//priorities[y][x] = priority;
	hasprinted[y][x] = bgpalettes[palette][coloridx] != 0;
}*/

void LCD::renderWindow(uint8_t y)
{
	uint16_t baseaddr = (uint8_t)mem[LCDC] & 0b01000000 ? LCD_BG2_BEGIN : LCD_BG1_BEGIN;
	uint8_t wx = (uint8_t)mem[WX] - 7;
	uint8_t wy = mem[WY];
	if (wx >= 144 || wy > y)
		return;
	for (uint8_t x = 0; x < 160; ++x)
	{
		uint8_t rx = wx + x;
		uint8_t ry = wy + y;
		uint8_t bx = rx % 8;
		uint8_t by = ry % 8;
		uint32_t addr = baseaddr + (rx - bx) + (ry - by) * 32;
		uint8_t charcode = mem.cbank0(addr);
		if (true/*DMG*/)
			renderBGCharDMG(x, y, bx, by, charcode);
		else/*CGB*/
			renderBGCharCGB(x, y, bx, by, charcode, mem.cbank1(addr));
	}
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
