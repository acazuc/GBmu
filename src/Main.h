#ifndef MAIN_H
# define MAIN_H

# include "DebugDisplay.h"
# include "MainDisplay.h"
# include "BindDisplay.h"
# include "Audio.h"
# include "LCD.h"
# include <string>

class Main
{

	private:
		static DebugDisplay *debugDisplay;
		static MainDisplay *mainDisplay;
		static BindDisplay *bindDisplay;
		static Audio *audio;
		static LCD *lcd;
		static uint64_t speedFactor;
		static bool paused;

	public:
		static void run(int ac, char **av);
		static void glErrors(std::string str);
		static void windowClosed();
		static DebugDisplay *getDebugDisplay() {return (debugDisplay);};
		static MainDisplay *getMainDisplay() {return (mainDisplay);};
		static BindDisplay *getBindDisplay() {return (bindDisplay);};
		static Audio *getAudio() {return (audio);};
		static LCD *getLcd() {return (lcd);};
		static void setPaused(bool paused) {Main::paused = paused;};
		static bool isPaused() {return (paused);};
		static void setSpeedFactor(uint64_t speedFactor) {Main::speedFactor = speedFactor;};

};

#endif
