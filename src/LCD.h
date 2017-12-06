#ifndef LCD_H
# define LCD_H

# include <memboy.h>

# define LCD_CHAR_BEGIN 0x8000
# define LCD_CHAR_END 0x8FFF
# define LCD_CHAR1_BEGIN 0x8000
# define LCD_CHAR1_END 0x8FFF
# define LCD_CHAR2_BEGIN 0x8800
# define LCD_CHAR2_END 0x97FF
# define LCD_OAM_BEGIN 0xFE00
# define LCD_OAM_END 0xFE9F
# define LCD_CHAR_LEN 0xf
# define LCD_BG1_BEGIN 0x9800
# define LCD_BG1_END 0x9BFF
# define LCD_BG2_BEGIN 0x9C00
# define LCD_BG2_END 0x9FFF

class LCD
{

	private:

	public:
		void render();
		void renderBG(uint8_t y);
		void renderOBJ(uint8_t y);
		void renderChars();
		void printChar(uint8_t cx, uint8_t cy, uint8_t charcode, bool hflip, bool vflip);

};

#endif
