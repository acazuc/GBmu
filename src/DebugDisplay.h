#ifndef DEBUG_DISPLAY_H
# define DEBUG_DISPLAY_H

# include <gtk/gtk.h>
# include <string>

class DebugDisplay
{

	private:
		GtkWidget *instructions;
		GtkWidget *scrolledinst;
		GtkWidget *scrolledregs;
		GtkWidget *registers;
		GtkWidget *nextStep;
		GtkWidget *window;
		bool displayed;
		void setInstructionsText(std::string text);
		void setRegistersText(std::string text);

	public:
		DebugDisplay();
		~DebugDisplay();
		void iter();
		void show();
		void hide();
		inline GtkWidget *getScrolledinst() {return (this->scrolledinst);};
		inline GtkWidget *getScrolledregs() {return (this->scrolledregs);};
		inline GtkWidget *getWindow() {return (this->window);};

};

#endif
