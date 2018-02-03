#ifndef DISPLAY_H
# define DISPLAY_H

# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <epoxy/gl.h>
# include <epoxy/glx.h>
# include <cstdint>

class MainDisplay
{

	private:
		GtkWidget *window;
		GtkWidget *gl;
		uint8_t *texDatas;
		uint8_t keys;

	public:
		MainDisplay();
		~MainDisplay();
		void iter();
		void putPixel(uint8_t x, uint8_t y, uint8_t *color);
		inline GtkWidget *getWindow() {return (this->window);};
		inline uint8_t *getTexDatas() {return (this->texDatas);};
		inline void setKeys(uint8_t keys) {this->keys = keys;};
		inline uint8_t getKeys() {return (this->keys);};

};

#endif
