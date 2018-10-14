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
	gtk_widget_set_size_request(Main::getDebugDisplay()->getRegisters(), width / 2, height);
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
	gtk_window_set_title(GTK_WINDOW(this->window), "GBmu debugger");
	gtk_window_resize(GTK_WINDOW(this->window), 640, 480);
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(cb_quit), NULL);
	GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	this->scrolledinst = gtk_scrolled_window_new(NULL, NULL);
	this->instructions = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(this->instructions), false);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(this->instructions), true);
	gtk_container_add(GTK_CONTAINER(this->scrolledinst), this->instructions);
	gtk_paned_add1(GTK_PANED(paned), this->scrolledinst);
	this->registers = gtk_fixed_new();
	char *empty = "";
	this->regsFlagsLabel = gtk_label_new(empty);
	gtk_fixed_put(GTK_FIXED(this->registers), this->regsFlagsLabel, 0, 0);
	gtk_paned_add2(GTK_PANED(paned), this->registers);
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

static char tohex(char c)
{
	c &= 0xf;
	if (c >= 10)
		return ('A' + c - 10);
	return ('0' + c);
}

static std::string build_regs(std::string name, uint8_t r1, uint8_t r2)
{
	return name + std::string(": ") + std::string(1, tohex(r1 >> 4)) + std::string(1, tohex(r1)) + std::string(" ") + std::string(1, tohex(r2 >> 4)) + std::string(1, tohex(r2)) + std::string("\n");
}

static std::string build_flag(std::string name, bool enabled)
{
	if (enabled)
		return std::string("<span color=\"green\">") + name + std::string("</span>");
	return std::string("<span color=\"red\">") + name + std::string("</span>");
}

void DebugDisplay::updateRegsFlags(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t h, uint8_t l)
{
	if (!this->displayed)
		return;
	std::string text;
	text += "<tt><span font=\"13\">";
	text += build_regs("AF ", a, f);
	text += build_regs("BC ", b, c);
	text += build_regs("DE ", d, e);
	text += build_regs("HL ", h, l);
	text += "Flags ";
	text += build_flag("Z", f & 0x80);
	text += build_flag("N", f & 0x40);
	text += build_flag("H", f & 0x20);
	text += build_flag("C", f & 0x10);
	text += "</span></tt>";
	gtk_label_set_markup(GTK_LABEL(this->regsFlagsLabel), text.c_str());
}
