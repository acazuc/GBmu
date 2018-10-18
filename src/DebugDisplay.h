#ifndef DEBUG_DISPLAY_H
# define DEBUG_DISPLAY_H

# include <gtk/gtk.h>
# include <string>

class DebugDisplay
{

	private:
		GtkWidget *regsFlagsLabel;
		GtkWidget *instructions;
		GtkWidget *scrolledinst;
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
		void updateRegsFlags(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t h, uint8_t l);
		inline GtkWidget *getScrolledinst() {return (this->scrolledinst);};
		inline GtkWidget *getRegisters() {return (this->registers);};
		inline GtkWidget *getWindow() {return (this->window);};

};

#endif
