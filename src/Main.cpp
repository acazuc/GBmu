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
	high_resolution_clock::time_point t0, t1, t2, t3;
	t0 = high_resolution_clock::now();
	t3 = high_resolution_clock::now();
	int fps = 0;
	while (true)
	{
		t1 = high_resolution_clock::now();
		auto basecount = duration_cast<nanoseconds>( t1 - t3 ).count();
		if (basecount > 1000000000  / 59.7)
		{
			t3 = t1;
			lcd->render();
			mainDisplay->iter();
			++fps;
			t2 = high_resolution_clock::now();
			basecount = duration_cast<nanoseconds>( t2 - t0 ).count();
			if (basecount > 1000000000)
			{
				t0 = t2;
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
