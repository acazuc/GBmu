#include "MainDisplay.h"
#include "jackshit.h"
#include "Main.h"
#include <cstring>
#include <iostream>
#include <fstream>

#define FILTER_NONE 0
#define FILTER_BILINEAR 1
#define FILTER_AASCALE2X 2
#define FILTER_AASCALE4X 3
#define FILTER_AASCALE8X 4
#define FILTER_SCALE2X 5
#define FILTER_SCALE4X 6
#define FILTER_SCALE8X 7
#define FILTER_HQ2X 8
#define FILTER_OMNISCALE 9
#define FILTER_SUPEREAGLE 10
#define FILTER_2XSAI 11
#define FILTER_XBR 12
#define FILTER_XBRZ 13
#define FILTER_GAMEBOY 14
#define FILTER_LAST 8

static float mat[16];
static int32_t ctx_width = -1;
static int32_t ctx_height = -1;
static GLuint texture;
static GLuint vao;
static uint64_t used_program = 0;

struct glprogram
{
	GLint texCoordsLocation;
	GLint vertexesLocation;
	GLint textureLocation;
	GLint mvpLocation;
	GLuint program;
};

static glprogram programs[FILTER_LAST];
static glprogram *currentprogram;

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

static void initProgram(glprogram *program, std::string vertex, std::string fragment)
{
	std::cout << "Creating shader with "  << vertex << " and " << fragment << std::endl;
	GLuint fs;
	GLuint vs;
	initVertexShader(vs, readfile(vertex));
	initFragmentShader(fs, readfile(fragment));
	program->program = glCreateProgram();
	glAttachShader(program->program, fs);
	glAttachShader(program->program, vs);
	glLinkProgram(program->program);
	GLint result = GL_FALSE;
	glGetProgramiv(program->program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int errorLen;
		glGetProgramiv(program->program, GL_INFO_LOG_LENGTH, &errorLen);
		char *error = new char[errorLen + 1];
		std::memset(error, 0, errorLen + 1);
		glGetProgramInfoLog(program->program, errorLen, NULL, error);
		std::cerr << "Program error:" << std::endl << error << std::endl;
		exit(EXIT_FAILURE);
	}
	glUseProgram(program->program);
	program->texCoordsLocation = glGetAttribLocation(program->program, "texCoords");
	program->vertexesLocation = glGetAttribLocation(program->program, "vertexes");
	program->textureLocation = glGetUniformLocation(program->program, "image");
	glUniform1i(program->textureLocation, 0);
	program->mvpLocation = glGetUniformLocation(program->program, "MVP");
	glUniformMatrix4fv(program->mvpLocation, 1, GL_FALSE, &mat[0]);
	glDetachShader(program->program, fs);
	glDetachShader(program->program, vs);
	glDeleteShader(fs);
	glDeleteShader(vs);
}

static void initPrograms()
{
	std::string fragments[] = {"basic.fs", "basic.fs", "AAScale2x.fs", "AAScale4x.fs", "AAScale8x.fs", "Scale2x.fs", "Scale4x.fs", "Scale8x.fs", "HQ2x.fs", "OmniScale.fs", "SuperEagle.fs", "2xsai.fs", "xbr.fs", "xbrz.fs", "Gameboy.fs"};
	for (uint8_t i = 0; i < FILTER_LAST; ++i)
		initProgram(&programs[i], "shaders/basic.vs", "shaders/" + fragments[i]);
	currentprogram = &programs[0];
}

static void initBuffers()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glUseProgram(currentprogram->program);
	glEnableVertexAttribArray(currentprogram->texCoordsLocation);
	glVertexAttribPointer(currentprogram->texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertex_info), (GLvoid*)(G_STRUCT_OFFSET(struct vertex_info, texCoords)));
	glEnableVertexAttribArray(currentprogram->vertexesLocation);
	glVertexAttribPointer(currentprogram->vertexesLocation, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertex_info), (GLvoid*)(G_STRUCT_OFFSET(struct vertex_info, position)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
}

static void gl_realize(GtkWidget *widget)
{
	GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(widget);
	if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
	{
		std::cerr << "gtk_widget_begin_gl failed" << std::endl;
		return;
	}
	glBlendEquation(GL_FUNC_ADD);
	glClearColor(0, 0, 0, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	initPrograms();
	initBuffers();
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	Main::glErrors("1");
	gdk_gl_drawable_gl_end(gldrawable);
}

static void gl_resize(GtkWidget *widget, gint width, gint height, gpointer osef)
{
	(void)widget;
	(void)osef;
	//std::cout << "width: " << width << ", height: " << height << std::endl;
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

static bool gl_render(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	(void)cr;
	(void)data;
	GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(widget);
	if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
	{
		std::cerr << "gtk_widget_begin_gl failed" << std::endl;
		return FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, used_program == 1 ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, used_program == 1 ? GL_LINEAR : GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE, Main::getMainDisplay()->getTexDatas());
	glBindVertexArray(vao);
	glUseProgram(currentprogram->program);
	glUniformMatrix4fv(currentprogram->mvpLocation, 1, GL_FALSE, &mat[0]);
	glUniform1i(currentprogram->textureLocation, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (ctx_width != widget->allocation.width || ctx_height != widget->allocation.height)
	{
		ctx_width = widget->allocation.width;
		ctx_height = widget->allocation.height;
		gl_resize(widget, ctx_width, ctx_height, NULL);
		float tmpw = ctx_width / 160.;
		float tmph = ctx_height / 144.;
		float tmp;
		if (tmpw > tmph)
			tmp = tmph;
		else
			tmp = tmpw;
		glViewport((ctx_width - tmp * 160) / 2, (ctx_height - tmp * 144) / 2, tmp * 160, tmp * 144);
	}
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	if (gdk_gl_drawable_is_double_buffered(gldrawable))
		gdk_gl_drawable_swap_buffers(gldrawable);
	else
		glFlush();
	Main::glErrors("main");
	gdk_gl_drawable_gl_end(gldrawable);
	return (TRUE);
}

//Choualbox dbar
static void cb_quit(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::windowClosed();
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
		corereset(filename);
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}

static void cb_file_quit(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	exit(EXIT_SUCCESS);
}

static void cb_edit_play(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::setPaused(false);
}

static void cb_edit_pause(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::setPaused(true);
}

static void cb_edit_restart(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	corereset();
}

static void cb_options_debug(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::getDebugDisplay()->show();
}

static void cb_options_binds(GtkWidget *osef1, gpointer osef2)
{
	(void)osef1;
	(void)osef2;
	Main::getBindDisplay()->show();
}

static void cb_options_mute(GtkWidget *widget, gpointer osef1)
{
	(void)osef1;
	Main::getAudio()->setMute(!Main::getAudio()->isMute());
	MainDisplay *mainDisplay = Main::getMainDisplay();
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_mute), Main::getAudio()->isMute());
}

static void cb_options_size(GtkWidget *osef1, gpointer size)
{
	(void)osef1;
	gtk_window_unmaximize(GTK_WINDOW(Main::getMainDisplay()->getWindow()));
	gtk_window_resize(GTK_WINDOW(Main::getMainDisplay()->getWindow()), 160 * (unsigned long)size, 144 * (unsigned long)size);
}

static void cb_options_mode(GtkWidget *widget, gpointer mode)
{
	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)))
		return;
	Main::setMode((uint64_t)mode);
	MainDisplay *mainDisplay = Main::getMainDisplay();
	if ((uint64_t)mode != MODE_AUTO)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_mode_auto), false);
	if ((uint64_t)mode != MODE_DMG)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_mode_dmg), false);
	if ((uint64_t)mode != MODE_CGB)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_mode_cgb), false);
}

static void cb_options_wave(GtkWidget *widget, gpointer type)
{
	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)))
		return;
	Main::getAudio()->getC12type() = (uint8_t)((uint64_t)type);
	MainDisplay *mainDisplay = Main::getMainDisplay();
	if ((uint64_t)type != AUDIO_C12_TYPE_SQUARE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_wave_square), false);
	if ((uint64_t)type != AUDIO_C12_TYPE_SAW)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_wave_saw), false);
	if ((uint64_t)type != AUDIO_C12_TYPE_TRIANGLE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_wave_triangle), false);
	if ((uint64_t)type != AUDIO_C12_TYPE_SINE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_wave_sine), false);
}

static void cb_options_filter(GtkWidget *widget, gpointer type)
{
	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)))
		return;
	used_program = (uint64_t)type;
	uint64_t id = used_program;
	if (id >= FILTER_LAST)
		id = FILTER_NONE;
	currentprogram = &programs[id];
	MainDisplay *mainDisplay = Main::getMainDisplay();
	if (id != FILTER_NONE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_none), false);
	if (id != FILTER_BILINEAR)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_bilinear), false);
	if (id != FILTER_AASCALE2X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_aascale2x), false);
	if (id != FILTER_AASCALE4X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_aascale4x), false);
	if (id != FILTER_AASCALE8X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_aascale8x), false);
	if (id != FILTER_SCALE2X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_scale2x), false);
	if (id != FILTER_SCALE4X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_scale4x), false);
	if (id != FILTER_SCALE8X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_scale8x), false);
	if (id != FILTER_HQ2X)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_hq2x), false);
	if (id != FILTER_OMNISCALE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_omniscale), false);
	if (id != FILTER_SUPEREAGLE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_supereagle), false);
	if (id != FILTER_2XSAI)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_2xsai), false);
	if (id != FILTER_XBR)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_xbr), false);
	if (id != FILTER_XBRZ)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_xbrz), false);
	if (id != FILTER_GAMEBOY)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_filter_gameboy), false);
}

static void cb_options_speed(GtkWidget *widget, gpointer data)
{
	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)))
		return;
	uint64_t speed = (uint64_t)data;
	Main::setSpeedFactor(speed);
	MainDisplay *mainDisplay = Main::getMainDisplay();
	if (speed != 1)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_1x), false);
	if (speed != 2)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_2x), false);
	if (speed != 4)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_4x), false);
	if (speed != 8)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_8x), false);
	if (speed != 16)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_16x), false);
	if (speed != 32)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_32x), false);
	if (speed != 64)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_64x), false);
	if (speed != 128)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_128x), false);
	if (speed != 0)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(mainDisplay->menu_options_speed_unlimited), false);
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
	char *authors[] = {(char*)"moi", (char*)"lui", NULL};
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), (const char**)authors);
	g_signal_connect(G_OBJECT(dialog), "destroy", G_CALLBACK(cb_dialog_quit), NULL);
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	(void)result;
	gtk_widget_destroy(dialog);
}

void MainDisplay::build_menu_file()
{
	this->menu_file = gtk_menu_item_new_with_label("File");
	this->menu_file_menu = gtk_menu_new();

	//Open
	this->menu_file_open = gtk_menu_item_new_with_label("Open");
	g_signal_connect(G_OBJECT(this->menu_file_open), "activate", G_CALLBACK(cb_file_open), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_file_menu), this->menu_file_open);

	//Quit
	this->menu_file_quit = gtk_menu_item_new_with_label("Quit");
	g_signal_connect(G_OBJECT(this->menu_file_quit), "activate", G_CALLBACK(cb_file_quit), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_file_menu), this->menu_file_quit);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_file), this->menu_file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu), this->menu_file);
}

void MainDisplay::build_menu_edit()
{
	this->menu_edit = gtk_menu_item_new_with_label("Edit");
	this->menu_edit_menu = gtk_menu_new();

	//Play
	this->menu_edit_play = gtk_menu_item_new_with_label("Play");
	g_signal_connect(G_OBJECT(this->menu_edit_play), "activate", G_CALLBACK(cb_edit_play), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_edit_menu), this->menu_edit_play);

	//Pause
	this->menu_edit_pause = gtk_menu_item_new_with_label("Pause");
	g_signal_connect(G_OBJECT(this->menu_edit_pause), "activate", G_CALLBACK(cb_edit_pause), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_edit_menu), this->menu_edit_pause);

	//Restart
	this->menu_edit_restart = gtk_menu_item_new_with_label("Restart");
	g_signal_connect(G_OBJECT(this->menu_edit_restart), "activate", G_CALLBACK(cb_edit_restart), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_edit_menu), this->menu_edit_restart);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_edit), this->menu_edit_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu), this->menu_edit);
}

void MainDisplay::build_menu_options_size()
{
	this->menu_options_size_menu = gtk_menu_new();
	for (uint8_t i = 1; i <= 20; ++i)
	{
		std::string a = std::to_string(160 * i) + "x" + std::to_string(144 * i);
		this->menu_options_size_item[i - 1] = gtk_menu_item_new_with_label(a.c_str());
		g_signal_connect(G_OBJECT(this->menu_options_size_item[i - 1]), "activate", G_CALLBACK(cb_options_size), (void*)((unsigned long)i));
		gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_size_menu), this->menu_options_size_item[i - 1]);
	}
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_options_size), this->menu_options_size_menu);
}

void MainDisplay::build_menu_options_mode()
{
	this->menu_options_mode_menu = gtk_menu_new();

	//Auto
	this->menu_options_mode_auto = gtk_check_menu_item_new_with_label("Auto");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this->menu_options_mode_auto), true);
	g_signal_connect(G_OBJECT(this->menu_options_mode_auto), "activate", G_CALLBACK(cb_options_mode), (void*)((unsigned long)MODE_AUTO));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_mode_menu), this->menu_options_mode_auto);

	//DMG
	this->menu_options_mode_dmg = gtk_check_menu_item_new_with_label("DMG");
	g_signal_connect(G_OBJECT(this->menu_options_mode_dmg), "activate", G_CALLBACK(cb_options_mode), (void*)((unsigned long)MODE_DMG));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_mode_menu), this->menu_options_mode_dmg);

	//CGB
	this->menu_options_mode_cgb = gtk_check_menu_item_new_with_label("CGB");
	g_signal_connect(G_OBJECT(this->menu_options_mode_cgb), "activate", G_CALLBACK(cb_options_mode), (void*)((unsigned long)MODE_CGB));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_mode_menu), this->menu_options_mode_cgb);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_options_mode), this->menu_options_mode_menu);
}

void MainDisplay::build_menu_options_wave()
{
	this->menu_options_wave_menu = gtk_menu_new();

	//Square
	this->menu_options_wave_square = gtk_check_menu_item_new_with_label("Square");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this->menu_options_wave_square), true);
	g_signal_connect(G_OBJECT(this->menu_options_wave_square), "activate", G_CALLBACK(cb_options_wave), (void*)((unsigned long)AUDIO_C12_TYPE_SQUARE));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_wave_menu), this->menu_options_wave_square);

	//Saw
	this->menu_options_wave_saw = gtk_check_menu_item_new_with_label("Saw");
	g_signal_connect(G_OBJECT(this->menu_options_wave_saw), "activate", G_CALLBACK(cb_options_wave), (void*)((unsigned long)AUDIO_C12_TYPE_SAW));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_wave_menu), this->menu_options_wave_saw);

	//Triangle
	this->menu_options_wave_triangle = gtk_check_menu_item_new_with_label("Triangle");
	g_signal_connect(G_OBJECT(this->menu_options_wave_triangle), "activate", G_CALLBACK(cb_options_wave), (void*)((unsigned long)AUDIO_C12_TYPE_TRIANGLE));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_wave_menu), this->menu_options_wave_triangle);

	//Sine
	this->menu_options_wave_sine = gtk_check_menu_item_new_with_label("Sine");
	g_signal_connect(G_OBJECT(this->menu_options_wave_sine), "activate", G_CALLBACK(cb_options_wave), (void*)((unsigned long)AUDIO_C12_TYPE_SINE));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_wave_menu), this->menu_options_wave_sine);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_options_wave), this->menu_options_wave_menu);
}

void MainDisplay::build_menu_options_filter()
{
	this->menu_options_filter_menu = gtk_menu_new();

	//None
	this->menu_options_filter_none = gtk_check_menu_item_new_with_label("None");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this->menu_options_filter_none), true);
	g_signal_connect(G_OBJECT(this->menu_options_filter_none), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_NONE));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_none);

	//Bilinear
	this->menu_options_filter_bilinear = gtk_check_menu_item_new_with_label("Bilinear");
	g_signal_connect(G_OBJECT(this->menu_options_filter_bilinear), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_BILINEAR));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_bilinear);

	//AAScale2x
	this->menu_options_filter_aascale2x = gtk_check_menu_item_new_with_label("AAScale2x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_aascale2x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_AASCALE2X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_aascale2x);

	//AAScale4x
	this->menu_options_filter_aascale4x = gtk_check_menu_item_new_with_label("AAScale4x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_aascale4x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_AASCALE4X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_aascale4x);

	//AAScale8x
	this->menu_options_filter_aascale8x = gtk_check_menu_item_new_with_label("AAScale8x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_aascale8x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_AASCALE8X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_aascale8x);

	//Scale2x
	this->menu_options_filter_scale2x = gtk_check_menu_item_new_with_label("Scale2x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_scale2x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_SCALE2X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_scale2x);

	//Scale4x
	this->menu_options_filter_scale4x = gtk_check_menu_item_new_with_label("Scale4x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_scale4x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_SCALE4X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_scale4x);

	//Scale8x
	this->menu_options_filter_scale8x = gtk_check_menu_item_new_with_label("Scale8x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_scale8x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_SCALE8X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_scale8x);

	//HQ2x
	this->menu_options_filter_hq2x = gtk_check_menu_item_new_with_label("HQ2x");
	g_signal_connect(G_OBJECT(this->menu_options_filter_hq2x), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_HQ2X));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_hq2x);

	//OmniScale
	this->menu_options_filter_omniscale = gtk_check_menu_item_new_with_label("OmniScale");
	g_signal_connect(G_OBJECT(this->menu_options_filter_omniscale), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_OMNISCALE));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_omniscale);

	//SuperEagle
	this->menu_options_filter_supereagle = gtk_check_menu_item_new_with_label("SuperEagle");
	g_signal_connect(G_OBJECT(this->menu_options_filter_supereagle), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_SUPEREAGLE));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_supereagle);

	//2xsai
	this->menu_options_filter_2xsai = gtk_check_menu_item_new_with_label("2xai");
	g_signal_connect(G_OBJECT(this->menu_options_filter_2xsai), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_2XSAI));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_2xsai);

	//xbr
	this->menu_options_filter_xbr = gtk_check_menu_item_new_with_label("xbr");
	g_signal_connect(G_OBJECT(this->menu_options_filter_xbr), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_XBR));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_xbr);

	//xbrz
	this->menu_options_filter_xbrz = gtk_check_menu_item_new_with_label("xbrz");
	g_signal_connect(G_OBJECT(this->menu_options_filter_xbrz), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_XBRZ));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_xbrz);

	//Gameboy
	this->menu_options_filter_gameboy = gtk_check_menu_item_new_with_label("Gameboy");
	g_signal_connect(G_OBJECT(this->menu_options_filter_gameboy), "activate", G_CALLBACK(cb_options_filter), (void*)((unsigned long)FILTER_GAMEBOY));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_filter_menu), this->menu_options_filter_gameboy);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_options_filter), this->menu_options_filter_menu);
}

void MainDisplay::build_menu_options_speed()
{
	this->menu_options_speed_menu = gtk_menu_new();

	//1x
	this->menu_options_speed_1x = gtk_check_menu_item_new_with_label("1x");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this->menu_options_speed_1x), true);
	g_signal_connect(G_OBJECT(this->menu_options_speed_1x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)1));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_1x);

	//2x
	this->menu_options_speed_2x = gtk_check_menu_item_new_with_label("2x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_2x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)2));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_2x);

	//4x
	this->menu_options_speed_4x = gtk_check_menu_item_new_with_label("4x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_4x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)4));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_4x);

	//8x
	this->menu_options_speed_8x = gtk_check_menu_item_new_with_label("8x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_8x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)8));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_8x);

	//16x
	this->menu_options_speed_16x = gtk_check_menu_item_new_with_label("16x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_16x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)16));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_16x);

	//32x
	this->menu_options_speed_32x = gtk_check_menu_item_new_with_label("32x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_32x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)32));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_32x);

	//64x
	this->menu_options_speed_64x = gtk_check_menu_item_new_with_label("64x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_64x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)64));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_64x);

	//128x
	this->menu_options_speed_128x = gtk_check_menu_item_new_with_label("128x");
	g_signal_connect(G_OBJECT(this->menu_options_speed_128x), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)128));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_128x);

	//Unlimited
	this->menu_options_speed_unlimited = gtk_check_menu_item_new_with_label("Unlimited");
	g_signal_connect(G_OBJECT(this->menu_options_speed_unlimited), "activate", G_CALLBACK(cb_options_speed), (void*)((unsigned long)0));
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_speed_menu), this->menu_options_speed_unlimited);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_options_speed), this->menu_options_speed_menu);
}

void MainDisplay::build_menu_options()
{
	this->menu_options = gtk_menu_item_new_with_label("Options");
	this->menu_options_menu = gtk_menu_new();

	//Debugger
	this->menu_options_debugger = gtk_menu_item_new_with_label("Debugger");
	g_signal_connect(G_OBJECT(this->menu_options_debugger), "activate", G_CALLBACK(cb_options_debug), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_debugger);

	//Binds
	this->menu_options_binds = gtk_menu_item_new_with_label("Binds");
	g_signal_connect(G_OBJECT(this->menu_options_binds), "activate", G_CALLBACK(cb_options_binds), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_binds);

	//Mute
	this->menu_options_mute = gtk_check_menu_item_new_with_label("Mute");
	g_signal_connect(G_OBJECT(this->menu_options_mute), "activate", G_CALLBACK(cb_options_mute), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_mute);

	//Size
	this->menu_options_size = gtk_menu_item_new_with_label("Size");
	build_menu_options_size();
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_size);

	//Mode
	this->menu_options_mode = gtk_menu_item_new_with_label("Mode");
	build_menu_options_mode();
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_mode);

	//Audio wave
	this->menu_options_wave = gtk_menu_item_new_with_label("Audio wave");
	build_menu_options_wave();
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_wave);

	//Filter
	this->menu_options_filter = gtk_menu_item_new_with_label("Filter");
	build_menu_options_filter();
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_filter);

	//Speed
	this->menu_options_speed = gtk_menu_item_new_with_label("Speed");
	build_menu_options_speed();
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_options_menu), this->menu_options_speed);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_options), this->menu_options_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu), this->menu_options);
}

void MainDisplay::build_menu_help()
{
	this->menu_help = gtk_menu_item_new_with_label("Help");
	this->menu_help_menu = gtk_menu_new();
	this->menu_help_about = gtk_menu_item_new_with_label("About");
	g_signal_connect(G_OBJECT(this->menu_help_about), "activate", G_CALLBACK(cb_help_about), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_help_menu), this->menu_help_about);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->menu_help), this->menu_help_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu), this->menu_help);
}

static int get_key_bit(int key)
{
	for (int i = 0; i < 8; ++i)
	{
		if (key == Main::getBindDisplay()->getBinds()[i])
			return (i);
	}
	return (-1);
}

static void cb_key_press_event(GtkWidget *osef1, GdkEventKey *event)
{
	(void)osef1;
	int bit = get_key_bit(event->keyval);
	if (bit != -1)
		Main::getMainDisplay()->setKeys(Main::getMainDisplay()->getKeys() | (1 << bit));
	else if (event->keyval == GDK_KEY_o && event->state & GDK_CONTROL_MASK)
		cb_file_open(NULL, NULL);
	else if (event->keyval == GDK_KEY_q && event->state & GDK_CONTROL_MASK)
		cb_file_quit(NULL, NULL);
	//std::cout << "Pressed" << std::endl;
	//std::cout << "keyval: " << gdk_keyval_name(event->keyval) << "(" << event->keyval << ")" << std::endl;
	//std::cout << "state: " << event->state << std::endl;
	//std::cout << "type: " << event->type << std::endl;
	//std::cout << std::endl;
}

static void cb_key_release_event(GtkWidget *osef1, GdkEventKey *event)
{
	(void)osef1;
	int bit = get_key_bit(event->keyval);
	if (bit != -1)
		Main::getMainDisplay()->setKeys(Main::getMainDisplay()->getKeys() & (~(1 << bit)));
	//std::cout << "Released" << std::endl;
	//std::cout << "keyval: " << gdk_keyval_name(event->keyval) << "(" << event->keyval << ")" << std::endl;
	//std::cout << "state: " << event->state << std::endl;
	//std::cout << "type: " << event->type << std::endl;
	//std::cout << std::endl;
}

MainDisplay::MainDisplay()
{
	this->keys = 0;
	this->texDatas = new uint8_t[160 * 144 * 3]();
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(this->window), "GBmu");
	gtk_window_set_resizable(GTK_WINDOW(this->window), TRUE);
	GdkGeometry geometry;
	//geometry.min_aspect = 1.111111111111;
	//geometry.max_aspect = 1.111111111111;
	//geometry.min_width = 160;
	//geometry.min_height = 144;
	//gtk_window_set_geometry_hints(GTK_WINDOW(this->window), NULL, &geometry, (GdkWindowHints)(GDK_HINT_MIN_SIZE));
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(cb_quit), NULL);
	g_signal_connect(G_OBJECT(this->window), "key-release-event", G_CALLBACK(cb_key_release_event), NULL);
	g_signal_connect(G_OBJECT(this->window), "key-press-event", G_CALLBACK(cb_key_press_event), NULL);
	GtkWidget *box = gtk_vbox_new(false, 0);
	this->menu = gtk_menu_bar_new();

	build_menu_file();
	build_menu_edit();
	build_menu_options();
	build_menu_help();

	gtk_widget_show_all(this->menu);
	gtk_box_pack_start(GTK_BOX(box), this->menu, FALSE, FALSE, 0);
	this->gl = gtk_drawing_area_new();
	GdkGLConfig *glconfig = gdk_gl_config_new_by_mode((GdkGLConfigMode)(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH/* | GDK_GL_MODE_DOUBLE*/));
	if (glconfig == NULL)
	{
		g_print("*** Cannot find the double-buffered visual.\n");
		g_print("*** Trying single-buffered visual.\n");
		glconfig = gdk_gl_config_new_by_mode((GdkGLConfigMode)(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH));
		if (glconfig == NULL)
		{
			g_print("*** No appropriate OpenGL-capable visual found.\n");
			exit(1);
		}
	}
	gtk_widget_set_gl_capability(this->gl, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);
	//gtk_widget_set_hexpand(this->gl, true);
	g_signal_connect(this->gl, "realize", G_CALLBACK(gl_realize), NULL);
	g_signal_connect(this->gl, "expose_event", G_CALLBACK(gl_render), NULL);
	gtk_widget_set_size_request(this->gl, 160, 144);
	gtk_container_add(GTK_CONTAINER(box), this->gl);
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

void MainDisplay::putPixel(uint8_t x, uint8_t y, uint8_t *color)
{
	uint32_t idx = (x + y * 160) * 3;
	std::memmove(this->texDatas + idx, color, 3);
}
