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
	audio = new Audio();
	audio->start();
	lcd = new LCD();
	high_resolution_clock::time_point fps_last, draw_last, tmp;
	fps_last = high_resolution_clock::now();
	draw_last = high_resolution_clock::now();
	int fps = 0;
	while (true)
	{
		tmp = high_resolution_clock::now();
		auto basecount = duration_cast<nanoseconds>( tmp - draw_last ).count();
		if (basecount > 1000000000  / 59.72750056960583276373)
		{
			draw_last = tmp;
			lcd->render();
			mainDisplay->iter();
			++fps;
			fps_last = high_resolution_clock::now();
			basecount = duration_cast<nanoseconds>( fps_last - tmp ).count();
			if (basecount > 1000000000)
			{
				tmp = fps_last;
				cout << "fps: " << dec << fps << endl;
				fps = 0;
			}
		}
		debugDisplay->iter();
		gtk_main_iteration_do(false);
	}
}

void Main::windowClosed()
{
	exit(EXIT_SUCCESS);
}

void Main::GLError(std::string text)
{
	GLenum glErr;
	while ((glErr = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << text << ": ";
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
