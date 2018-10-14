#include "Main.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <jackshit.h>
#include <cstring>
#include <thread>
#include <chrono>

using namespace chrono;

DebugDisplay *Main::debugDisplay;
MainDisplay *Main::mainDisplay;
BindDisplay *Main::bindDisplay;
Audio *Main::audio;
LCD *Main::lcd;
uint64_t Main::speedFactor = 1;
uint8_t Main::mode = 0;
bool Main::paused;

void Main::run(int ac, char **av)
{
	(void)ac;
	(void)av;
	paused = false;
	if (ac < 2)
	{
		std::cerr << "mdr no" << std::endl;
		exit(EXIT_FAILURE);
	}
	coremaster(av[1]);
	debugDisplay = new DebugDisplay();
	mainDisplay = new MainDisplay();
	bindDisplay = new BindDisplay();
	lcd = new LCD();
	audio = new Audio();
	audio->start();
	high_resolution_clock::time_point fps_last, draw_last, render_last, tmp;
	fps_last = high_resolution_clock::now();
	draw_last = high_resolution_clock::now();
	render_last = high_resolution_clock::now();
	int fps = 0;
	while (true)
	{
		core::mem.sysregs(0xFF03) = 0xFF;
		core::mem.sysregs(SC) = 0x7E;
		core::mem.sysregs(IF) = 0xE0;
		tmp = high_resolution_clock::now();
		auto basecount = duration_cast<nanoseconds>(tmp - draw_last).count();
		if (!speedFactor || basecount > 1000000000  / (59.72750056960583276373 * speedFactor))
		{
			draw_last = tmp;
			++fps;
			tmp = high_resolution_clock::now();
			basecount = duration_cast<nanoseconds>(tmp - fps_last).count();
			if (basecount > 1000000000)
			{
				fps_last = tmp;
				cout << "fps: " << dec << fps << endl;
				fps = 0;
			}
			lcd->render();
		}
		tmp = high_resolution_clock::now();
		basecount = duration_cast<nanoseconds>(tmp - render_last).count();
		if (basecount > 1000000000 / 60.)
		{
			render_last = tmp;
			mainDisplay->iter();
		}
		debugDisplay->iter();
		gtk_main_iteration_do(false);
	}
}

void Main::glErrors(std::string err)
{
	GLenum glErr;
	while ((glErr = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << err << ": ";
		if (glErr == GL_INVALID_ENUM)
			std::cerr << "GL_INVALID_ENUM" << std::endl;
		else if (glErr == GL_INVALID_VALUE)
			std::cerr << "GL_INVALID_VALUE" << std::endl;
		else if (glErr == GL_INVALID_OPERATION)
			std::cerr << "GL_INVALID_OPERATION" << std::endl;
		else if (glErr == GL_STACK_OVERFLOW)
			std::cerr << "GL_STACK_OVERFLOW" << std::endl;
		else if (glErr == GL_STACK_UNDERFLOW)
			std::cerr << "GL_STACK_UNDERFLOW" << std::endl;
		else if (glErr == GL_OUT_OF_MEMORY)
			std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
	}
}

void Main::windowClosed()
{
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	if (Pa_Initialize())
	{
		std::cerr << "Failed to init PA" << std::endl;
		return (-1);
	}
	gtk_init(&ac, &av);
	Main::run(ac, av);
	return (0);
}
