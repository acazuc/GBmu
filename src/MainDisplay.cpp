#include "MainDisplay.h"
#include "Main.h"
#include <cstring>
#include <iostream>

static int32_t ctx_width = 160;
static int32_t ctx_height = 144;
static bool initialized = false;

static void gl_render(GtkGLArea *area, GdkGLContext *context)
{
	if (!initialized && !area)
		return;
	(void)area;
	(void)context;
	std::cout << (const char*)glGetString(GL_RENDERER) << std::endl;
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!initialized)
	{
		initialized = true;
		MainDisplay *display = Main::getMainDisplay();
		glGenBuffers(1, &display->getTexCoords());
		glGenBuffers(1, &display->getVertexes());
	}
}

static void gl_resize(GtkGLArea *area, gint width, gint height, gpointer osef)
{
	(void)area;
	(void)osef;
	std::cout << "width: " << width << ", height: " << height << std::endl;
	ctx_width = width;
	ctx_height = height;
}

       //Choualbox dbar
static void cb_quit(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::windowClosed();
}

static void cb_file_quit(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	//
}

static void cb_file_open(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	//
}

static void cb_tool_debug(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::getDebugDisplay()->show();
}

MainDisplay::MainDisplay()
{
	this->texDatas = new uint8_t[160 * 144 * 3];
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(this->window), "GBmu");
	gtk_window_set_resizable(GTK_WINDOW(this->window), TRUE);
	GdkGeometry geometry;
	geometry.min_aspect = 1.111111111111;
	geometry.max_aspect = 1.111111111111;
	geometry.min_width = 160;
	geometry.min_height = 144;
	gtk_window_set_geometry_hints(GTK_WINDOW(this->window), NULL, &geometry, (GdkWindowHints)(GDK_HINT_ASPECT | GDK_HINT_MIN_SIZE));
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(cb_quit), NULL);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	g_object_set(box, "expand", TRUE, NULL);
	GtkWidget *menubar = gtk_menu_bar_new();

	//File
	GtkWidget *file = gtk_menu_item_new_with_label("File");
	gtk_widget_show(file);
	GtkWidget *file_menu = gtk_menu_new();
	gtk_widget_show(file_menu);
	GtkWidget *file_open = gtk_menu_item_new_with_label("Open");
	g_signal_connect(G_OBJECT(file_open), "activate", G_CALLBACK(cb_file_open), NULL);
	gtk_widget_show(file_open);
	GtkWidget *file_quit = gtk_menu_item_new_with_label("Quit");
	g_signal_connect(G_OBJECT(file_quit), "activate", G_CALLBACK(cb_file_quit), NULL);
	gtk_widget_show(file_quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_open);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	//Tools
	GtkWidget *tool = gtk_menu_item_new_with_label("Tools");
	gtk_widget_show(tool);
	GtkWidget *tool_menu = gtk_menu_new();
	gtk_widget_show(tool_menu);
	GtkWidget *tool_debug = gtk_menu_item_new_with_label("Debugger");
	g_signal_connect(G_OBJECT(tool_debug), "activate", G_CALLBACK(cb_tool_debug), NULL);
	gtk_widget_show(tool_debug);
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_menu), tool_debug);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(tool), tool_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), tool);

	gtk_widget_show(menubar);
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);
	this->gl = gtk_gl_area_new();
	gtk_widget_set_hexpand(this->gl, true);
	g_signal_connect(this->gl, "resize", G_CALLBACK(gl_resize), NULL);
	gtk_widget_set_size_request(this->gl, 160, 144);
	gtk_container_add(GTK_CONTAINER(box), this->gl);
	g_object_set(this->gl, "expand", TRUE, NULL);
	gtk_widget_show(this->gl);
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(this->window), box);
	//Display
	gtk_widget_show(this->window);
}

MainDisplay::~MainDisplay()
{
	gtk_widget_destroy(this->window);
}

void MainDisplay::iter()
{
	gtk_main_iteration_do(false);
	gl_render(NULL, NULL);
}

void MainDisplay::putPixel(int32_t x, int32_t y, int32_t color)
{
	std::memcpy(this->texDatas + (x + y * 160) * 4, ((uint8_t*)&color) + 1, 3);
}
