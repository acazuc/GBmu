#ifndef DEBUG_DISPLAY_H
# define DEBUG_DISPLAY_H

# include <gtk/gtk.h>

class DebugDisplay
{

	private:
		GtkWidget *window;
		bool displayed;

	public:
		DebugDisplay();
		~DebugDisplay();
		void iter();
		void show();
		void hide();

};

#endif
