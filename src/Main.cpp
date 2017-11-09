#include "Main.h"
#include <unistd.h>
#include <stdlib.h>

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

int main(int ac, char **av)
{
	gtk_init(&ac, &av);
	Main::run(ac, av);
	return (0);
}
