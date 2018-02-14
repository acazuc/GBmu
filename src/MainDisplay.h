#ifndef DISPLAY_H
# define DISPLAY_H

# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <epoxy/gl.h>
# include <epoxy/glx.h>
# include <cstdint>

class MainDisplay
{

	public:
		GtkWidget *menu;
		GtkWidget *menu_file;
		GtkWidget *menu_file_menu;
		GtkWidget *menu_file_open;
		GtkWidget *menu_file_quit;
		GtkWidget *menu_edit;
		GtkWidget *menu_edit_menu;
		GtkWidget *menu_edit_play;
		GtkWidget *menu_edit_pause;
		GtkWidget *menu_edit_restart;
		GtkWidget *menu_options;
		GtkWidget *menu_options_menu;
		GtkWidget *menu_options_debugger;
		GtkWidget *menu_options_binds;
		GtkWidget *menu_options_size;
		GtkWidget *menu_options_size_menu;
		GtkWidget *menu_options_size_item[20];
		GtkWidget *menu_options_mode;
		GtkWidget *menu_options_mode_menu;
		GtkWidget *menu_options_mode_auto;
		GtkWidget *menu_options_mode_dmg;
		GtkWidget *menu_options_mode_cgb;
		GtkWidget *menu_options_wave;
		GtkWidget *menu_options_wave_menu;
		GtkWidget *menu_options_wave_square;
		GtkWidget *menu_options_wave_saw;
		GtkWidget *menu_options_wave_triangle;
		GtkWidget *menu_options_wave_sine;
		GtkWidget *menu_options_filter;
		GtkWidget *menu_options_filter_menu;
		GtkWidget *menu_options_filter_none;
		GtkWidget *menu_options_filter_aascale2x;
		GtkWidget *menu_options_filter_aascale4x;
		GtkWidget *menu_options_filter_aascale8x;
		GtkWidget *menu_options_filter_scale2x;
		GtkWidget *menu_options_filter_scale4x;
		GtkWidget *menu_options_filter_scale8x;
		GtkWidget *menu_options_filter_hq2x;
		GtkWidget *menu_options_filter_omniscale;
		GtkWidget *menu_options_filter_supereagle;
		GtkWidget *menu_options_filter_2xsai;
		GtkWidget *menu_options_filter_xbr;
		GtkWidget *menu_options_filter_xbrz;
		GtkWidget *menu_options_filter_gameboy;
		GtkWidget *menu_options_speed;
		GtkWidget *menu_options_speed_menu;
		GtkWidget *menu_options_speed_1x;
		GtkWidget *menu_options_speed_2x;
		GtkWidget *menu_options_speed_4x;
		GtkWidget *menu_options_speed_8x;
		GtkWidget *menu_options_speed_16x;
		GtkWidget *menu_options_speed_32x;
		GtkWidget *menu_options_speed_64x;
		GtkWidget *menu_options_speed_128x;
		GtkWidget *menu_options_speed_unlimited;
		GtkWidget *menu_help;
		GtkWidget *menu_help_menu;
		GtkWidget *menu_help_about;
		GtkWidget *window;
		GtkWidget *gl;

	private:
		uint8_t *texDatas;
		uint8_t keys;
		void build_menu_file();
		void build_menu_edit();
		void build_menu_options_size();
		void build_menu_options_mode();
		void build_menu_options_wave();
		void build_menu_options_filter();
		void build_menu_options_speed();
		void build_menu_options();
		void build_menu_help();

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
