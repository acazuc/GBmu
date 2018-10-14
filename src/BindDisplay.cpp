#include "BindDisplay.h"
#include "Main.h"
#include <iostream>
#include <cstring>

gint bposx[] =		{100, 200, 150, 150, 300, 400, 500, 600, 300, 400};
gint bposy[] =		{85 , 85 , 55 , 115, 250, 250, 90 , 60 , 350, 350};

gint lposx[] =		{0  , 300, 150, 150, 300, 400, 400, 700, 300, 400};
gint lposy[] =		{85 , 85 , 20 , 150, 280, 280, 90 , 60 , 380, 380};
gfloat lxalign[] =	{1  , 0  , .5 , .5 , .5 , .5 , 1  , 0  , .5 , .5};
gfloat lyalign[] =	{.5 , .5 , 1  , 0  , 0  , 0  , .5 , .5 , 0  , 0};

std::string labels_texts[] = {"Left", "Right", "Up", "Down", "Select", "Start", "B", "A", "Save state", "Load state"};

//               Left    Right  Up     Down  rctrl  rshift num0   num3
gint dbinds[] = {65361, 65363, 65362, 65364, 65508, 65506, 65456, 65459, 0, 0};

int focused = -1;

static void cb_quit(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::getBindDisplay()->hide();
}

static void cb_bind_press(GtkWidget *osef1, gpointer id)
{
	(void)osef1;
	gtk_button_set_label(GTK_BUTTON(Main::getBindDisplay()->getButton((int)((int64_t)id))), std::string("?").c_str());
	focused = (int64_t)id;
}

static void cb_key_press_event(GtkWidget *osef1, GdkEventKey *event)
{
	(void)osef1;
	if (focused == -1)
		return;
	if (event->keyval == 65307) //Escape
	{
		gtk_button_set_label(GTK_BUTTON(Main::getBindDisplay()->getButton(focused)), gdk_keyval_name(Main::getBindDisplay()->getBinds()[focused]));
		focused = -1;
		return;
	}
	gtk_button_set_label(GTK_BUTTON(Main::getBindDisplay()->getButton(focused)), gdk_keyval_name(event->keyval));
	Main::getBindDisplay()->getBinds()[focused] = event->keyval;
	Main::getBindDisplay()->writeBinds();
	focused = -1;
}

BindDisplay::BindDisplay()
: window(NULL)
, displayed(false)
{
	std::memset(binds, 0, sizeof(binds));
	std::ifstream ifs("binds");
	if (!ifs.is_open())
	{
		for (uint8_t i = 0; i < BINDS; ++i)
			binds[i] = dbinds[i];
		writeBinds();
		return;
	}
	uint8_t i = 0;
	std::string s;
	try
	{
		while (i < BINDS && getline(ifs, s))
		{
			try
			{
				binds[i] = std::stoi(s);
			}
			catch (std::exception e)
			{
				binds[i] = dbinds[i];
			}
			++i;
		}
	}
	catch (std::exception &e)
	{
		i = 0;
	}
	if (i != BINDS)
	{
		for (uint8_t i = 0; i < BINDS; ++i)
			binds[i] = dbinds[i];
		writeBinds();
	}
}

BindDisplay::~BindDisplay()
{
	hide();
}

void BindDisplay::writeBinds()
{
	std::ofstream ofs("binds", ios_base::out | ios_base::trunc);
	if (!ofs.is_open())
	{
		std::cerr << "please make binds file available, don't be such a dick" << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		for (uint8_t i = 0; i < BINDS; ++i)
			ofs << binds[i] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "please make binds file available, don't be such a dick" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (ofs.fail())
	{
		std::cerr << "please make binds file available, don't be such a dick" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void BindDisplay::show()
{
	if (this->displayed)
	{
		gtk_window_present(GTK_WINDOW(this->window));
		return;
	}
	this->displayed = true;
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(this->window), "GBmu binds");
	g_signal_connect(G_OBJECT(this->window), "key-press-event", G_CALLBACK(cb_key_press_event), NULL);
	gtk_window_set_resizable(GTK_WINDOW(this->window), false);
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(cb_quit), NULL);
	GtkWidget *fixed = gtk_fixed_new();
	for (uint8_t i = 0; i < BINDS; ++i)
	{
		this->buttons[i] = gtk_button_new_with_label(gdk_keyval_name(binds[i]));
		gtk_widget_set_size_request(this->buttons[i], 100, 30);
		g_signal_connect(G_OBJECT(this->buttons[i]), "clicked", G_CALLBACK(cb_bind_press), (gpointer)((int64_t)i));
		gtk_fixed_put(GTK_FIXED(fixed), this->buttons[i], bposx[i], bposy[i]);
		this->labels[i] = gtk_label_new(labels_texts[i].c_str());
		gtk_label_set_xalign(GTK_LABEL(this->labels[i]), lxalign[i]);
		gtk_label_set_yalign(GTK_LABEL(this->labels[i]), lyalign[i]);
		gtk_widget_set_size_request(this->labels[i], 100, 30);
		gtk_fixed_put(GTK_FIXED(fixed), this->labels[i], lposx[i], lposy[i]);
	}
	gtk_widget_set_size_request(fixed, 750, 400);
	gtk_container_add(GTK_CONTAINER(this->window), fixed);
	gtk_widget_show_all(this->window);
}

void BindDisplay::hide()
{
	if (!this->displayed)
		return;
	this->displayed = false;
	gtk_widget_destroy(this->window);
}
