#ifndef BIND_DISPLAY_H
# define BIND_DISPLAY_H

# include <gtk/gtk.h>
# include <cstdint>

# define BIND_L 0
# define BIND_R 1
# define BIND_U 2
# define BIND_D 3
# define BIND_SE 4
# define BIND_ST 5
# define BIND_B 6
# define BIND_A 7
# define BIND_SAVE_STATE 8
# define BIND_LOAD_STATE 9

# define BINDS 10

class BindDisplay
{

	private:
		GtkWidget *buttons[BINDS];
		GtkWidget *labels[BINDS];
		GtkWidget *window;
		guint binds[BINDS];
		bool displayed;

	public:
		BindDisplay();
		~BindDisplay();
		void show();
		void hide();
		void writeBinds();
		GtkWidget *getButton(uint8_t i) {return (this->buttons[i]);};
		guint *getBinds() {return (binds);};

};

#endif
