#include "DebugDisplay.h"
#include "Main.h"

static void cb_quit(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::getDebugDisplay()->hide();
}

DebugDisplay::DebugDisplay()
: window(NULL)
, displayed(false)
{
	//Empty
}

DebugDisplay::~DebugDisplay()
{
	gtk_widget_destroy(this->window);
}

void DebugDisplay::show()
{
	if (this->displayed)
	{
		gtk_window_present(GTK_WINDOW(this->window));
		return;
	}
	this->displayed = true;
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(cb_quit), NULL);
	gtk_widget_show(this->window);
}

void DebugDisplay::hide()
{
	if (!this->displayed)
		return;
	this->displayed = false;
	gtk_widget_destroy(this->window);
}
