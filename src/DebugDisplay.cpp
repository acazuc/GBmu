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
	hide();
}

void DebugDisplay::setInstructionsText(std::string text)
{
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->instructions));
	gtk_text_buffer_set_text(buf, text.c_str(), text.length());
}

void DebugDisplay::setRegistersText(std::string text)
{
	GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->registers));
	gtk_text_buffer_set_text(buf, text.c_str(), text.length());
}

void DebugDisplay::iter()
{
	if (!this->displayed)
		return;
	gint width;
	gint height;
	gtk_window_get_size(GTK_WINDOW(Main::getDebugDisplay()->getWindow()), &width, &height);
	gtk_widget_set_size_request(Main::getDebugDisplay()->getScrolledinst(), width / 2, height);
	gtk_widget_set_size_request(Main::getDebugDisplay()->getScrolledregs(), width / 2, height);
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
	gtk_window_resize(GTK_WINDOW(this->window), 640, 480);
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(cb_quit), NULL);
	GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	this->scrolledinst = gtk_scrolled_window_new(NULL, NULL);
	this->instructions = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(this->instructions), false);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(this->instructions), true);
	gtk_container_add(GTK_CONTAINER(this->scrolledinst), this->instructions);
	gtk_paned_add1(GTK_PANED(paned), this->scrolledinst);
	this->scrolledregs = gtk_scrolled_window_new(NULL, NULL);
	this->registers = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(this->registers), false);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(this->registers), true);
	gtk_container_add(GTK_CONTAINER(this->scrolledregs), this->registers);
	gtk_paned_add2(GTK_PANED(paned), this->scrolledregs);
	gtk_container_add(GTK_CONTAINER(this->window), paned);
	gtk_widget_show_all(this->window);
}

void DebugDisplay::hide()
{
	if (!this->displayed)
		return;
	this->displayed = false;
	gtk_widget_destroy(this->window);
}
