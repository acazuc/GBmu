#ifndef AUDIO_H
# define AUDIO_H

# include <portaudio.h>
# include <cstdint>

/*
1: rectangle with sweep and envelope
2: rectangle with envelope
3: input of RAM
4: white noise with envelope
*/

class Audio
{

	private:
		PaStream *stream;

	public:
		Audio();
		~Audio();

};

#endif
