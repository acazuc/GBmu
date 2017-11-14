#include "MainDisplay.h"
#include "Main.h"
#include <cstring>
#include <iostream>
#include <fstream>

static float mat[16];
static int32_t ctx_width = 160;
static int32_t ctx_height = 144;
static GLint texCoordsLocation;
static GLint vertexesLocation;
static GLint textureLocation;
static GLint mvpLocation;
static GLuint program;
static GLuint texture;
static GLuint vao;

struct vertex_info
{
	float texCoords[2];
	float position[2];
};

static const struct vertex_info vertex_data[] =
{
	{{0, 0}, {0, 0}},
	{{1, 0}, {1, 0}},
	{{0, 1}, {0, 1}},
	{{1, 0}, {1, 0}},
	{{1, 1}, {1, 1}},
	{{0, 1}, {0, 1}}
};

static void initFragmentShader(GLuint &fs, std::string shader)
{
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *tamer = shader.c_str();
	glShaderSource(fs, 1, &tamer, NULL);
	glCompileShader(fs);
	GLint result = GL_FALSE;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int errorLen;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &errorLen);
		char *error = new char[errorLen + 1];
		std::memset(error, 0, errorLen + 1);
		glGetShaderInfoLog(fs, errorLen, NULL, error);
		std::cerr << "Fragment shader error: " << std::endl << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

static void initVertexShader(GLuint &vs, std::string shader)
{
	vs = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *tamer = shader.c_str();
	glShaderSource(vs, 1, &tamer, NULL);
	glCompileShader(vs);
	GLint result = GL_FALSE;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int errorLen;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &errorLen);
		char *error = new char[errorLen + 1];
		std::memset(error, 0, errorLen + 1);
		glGetShaderInfoLog(vs, errorLen, NULL, error);
		std::cerr << "Vertex shader error: " << std::endl << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

static std::string readfile(std::string file)
{
	std::ifstream ifs(file);
	return (std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()));
}

static void initProgram()
{
	GLuint fs;
	GLuint vs;
	initFragmentShader(fs, readfile("shaders/basic.fs"));
	initVertexShader(vs, readfile("shaders/basic.vs"));
	program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);
	GLint result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int errorLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLen);
		char *error = new char[errorLen + 1];
		std::memset(error, 0, errorLen + 1);
		glGetProgramInfoLog(program, errorLen, NULL, error);
		std::cerr << "Program error:" << std::endl << error << std::endl;
		exit(EXIT_FAILURE);
	}
	glUseProgram(program);
	texCoordsLocation = glGetAttribLocation(program, "texCoords");
	vertexesLocation = glGetAttribLocation(program, "vertexes");
	textureLocation = glGetUniformLocation(program, "texture");
	glUniform1i(textureLocation, 0);
	mvpLocation = glGetUniformLocation(program, "MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mat[0]);
	glDetachShader(program, fs);
	glDetachShader(program, vs);
	glDeleteShader(fs);
	glDeleteShader(vs);
}

static void initBuffers()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(texCoordsLocation);
	glVertexAttribPointer(texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertex_info), (GLvoid*)(G_STRUCT_OFFSET(struct vertex_info, texCoords)));
	glEnableVertexAttribArray(vertexesLocation);
	glVertexAttribPointer(vertexesLocation, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertex_info), (GLvoid*)(G_STRUCT_OFFSET(struct vertex_info, position)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
}

static void gl_realize(GtkGLArea *area)
{
	(void)area;
	gtk_gl_area_make_current(area);
	glBlendEquation(GL_FUNC_ADD);
	glClearColor(0, 0, 0, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	initProgram();
	initBuffers();
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

static bool gl_render(GtkGLArea *area, GdkGLContext *context)
{
	(void)area;
	(void)context;
	gdk_gl_context_make_current(context);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE, Main::getMainDisplay()->getTexDatas());
	//std::cout << (const char*)glGetString(GL_RENDERER) << std::endl;
	//glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(mat[0]));
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glFlush();
	return (TRUE);
}

static void gl_resize(GtkGLArea *area, gint width, gint height, gpointer osef)
{
	(void)area;
	(void)osef;
	std::cout << "width: " << width << ", height: " << height << std::endl;
	ctx_width = width;
	ctx_height = height;
	mat[0] = 2 / 1;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 0;
	mat[4] = 0;
	mat[5] = 2 / -1;
	mat[6] = 0;
	mat[7] = 0;
	mat[8] = 0;
	mat[9] = 0;
	mat[10] = -2 / 4;
	mat[11] = 0;
	mat[12] = -1;
	mat[13] = 1;
	mat[14] = 0;
	mat[15] = 1;
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
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(Main::getMainDisplay()->getWindow()), action, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		std::cout << "Opened file " << filename << std::endl;
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}

static void cb_tool_debug(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::getDebugDisplay()->show();
}

static void cb_tool_size(GtkWidget *osef1, gpointer size)
{
	(void)osef1;
	gtk_window_unmaximize(GTK_WINDOW(Main::getMainDisplay()->getWindow()));
	gtk_window_resize(GTK_WINDOW(Main::getMainDisplay()->getWindow()), 160 * (unsigned long)size, 144 * (unsigned long)size);
}

static void cb_dialog_quit(GtkWidget *dialog, gpointer osef1)
{
	(void)osef1;
	gtk_widget_destroy(dialog);
}

static void cb_help_about(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "GBmu");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "2 mecs un peu foufou");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "So many emulation right now");
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), "xdbcp license v1");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://github.com/acazuc/GBmu");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), "Le github interdit");
	char *authors[2] = {(char*)"moi", (char*)"lui"};
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), (const char**)authors);
	g_signal_connect(G_OBJECT(dialog), "destroy", G_CALLBACK(cb_dialog_quit), NULL);
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	(void)result;
	gtk_widget_destroy(dialog);
}

static void cb_tool_wave(GtkWidget *osef1, gpointer type)
{
	(void)osef1;
	Main::getAudio()->getC12type() = (uint8_t)((uint64_t)type);
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
	GtkWidget *file_menu = gtk_menu_new();
	GtkWidget *file_open = gtk_menu_item_new_with_label("Open");
	g_signal_connect(G_OBJECT(file_open), "activate", G_CALLBACK(cb_file_open), NULL);
	GtkWidget *file_quit = gtk_menu_item_new_with_label("Quit");
	g_signal_connect(G_OBJECT(file_quit), "activate", G_CALLBACK(cb_file_quit), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_open);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	//Tools
	GtkWidget *tool = gtk_menu_item_new_with_label("Tools");
	GtkWidget *tool_menu = gtk_menu_new();
	GtkWidget *tool_debug = gtk_menu_item_new_with_label("Debugger");
	g_signal_connect(G_OBJECT(tool_debug), "activate", G_CALLBACK(cb_tool_debug), NULL);
	GtkWidget *tool_size_menu = gtk_menu_new();
	GtkWidget *tool_size = gtk_menu_item_new_with_label("Size");
	for (uint8_t i = 1; i < 20; ++i)
	{
		std::string a = std::to_string(160 * i) + "x" + std::to_string(144 * i);
		GtkWidget *tool_size_x = gtk_menu_item_new_with_label(a.c_str());
		g_signal_connect(G_OBJECT(tool_size_x), "activate", G_CALLBACK(cb_tool_size), (void*)((unsigned long)i));
		gtk_menu_shell_append(GTK_MENU_SHELL(tool_size_menu), tool_size_x);
	}
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(tool_size), tool_size_menu);
	GtkWidget *tool_wave_menu = gtk_menu_new();
	GtkWidget *tool_wave = gtk_menu_item_new_with_label("Audio Wave");
	GtkWidget *tool_wave_square = gtk_menu_item_new_with_label("Square");
	g_signal_connect(G_OBJECT(tool_wave_square), "activate", G_CALLBACK(cb_tool_wave), (void*)((unsigned long)AUDIO_C12_TYPE_SQUARE));
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_wave_menu), tool_wave_square);
	GtkWidget *tool_wave_saw = gtk_menu_item_new_with_label("Saw");
	g_signal_connect(G_OBJECT(tool_wave_saw), "activate", G_CALLBACK(cb_tool_wave), (void*)((unsigned long)AUDIO_C12_TYPE_SAW));
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_wave_menu), tool_wave_saw);
	GtkWidget *tool_wave_sin = gtk_menu_item_new_with_label("Sin");
	g_signal_connect(G_OBJECT(tool_wave_sin), "activate", G_CALLBACK(cb_tool_wave), (void*)((unsigned long)AUDIO_C12_TYPE_SIN));
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_wave_menu), tool_wave_sin);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(tool_wave), tool_wave_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_menu), tool_debug);
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_menu), tool_size);
	gtk_menu_shell_append(GTK_MENU_SHELL(tool_menu), tool_wave);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(tool), tool_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), tool);
	//Help
	GtkWidget *help = gtk_menu_item_new_with_label("Help");
	GtkWidget *help_menu = gtk_menu_new();
	GtkWidget *help_about = gtk_menu_item_new_with_label("About");
	g_signal_connect(G_OBJECT(help_about), "activate", G_CALLBACK(cb_help_about), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_about);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), help_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

	gtk_widget_show_all(menubar);
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);
	this->gl = gtk_gl_area_new();
	gtk_widget_set_hexpand(this->gl, true);
	g_signal_connect(this->gl, "realize", G_CALLBACK(gl_realize), NULL);
	g_signal_connect(this->gl, "resize", G_CALLBACK(gl_resize), NULL);
	g_signal_connect(this->gl, "render", G_CALLBACK(gl_render), NULL);
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
	gtk_widget_queue_draw(this->window);
}

void MainDisplay::putPixel(int32_t x, int32_t y, int32_t color)
{
	std::memcpy(this->texDatas + (x + y * 160) * 4, ((uint8_t*)&color) + 1, 3);
}
