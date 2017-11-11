#include "Main.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

DebugDisplay *Main::debugDisplay;
MainDisplay *Main::mainDisplay;

void Main::run(int ac, char **av)
{
	(void)ac;
	(void)av;
	debugDisplay = new DebugDisplay();
	mainDisplay = new MainDisplay();
	while (true)
	{
		mainDisplay->iter();
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
	gtk_init(&ac, &av);
	Main::run(ac, av);
	return (0);
}
