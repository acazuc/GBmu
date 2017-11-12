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

# define AUDIO_MODE_1 0x1
# define AUDIO_MODE_2 0x2
# define AUDIO_MODE_3 0x4
# define AUDIO_MODE_4 0x8

class Audio
{

	private:
		PaStream *stream;
		uint8_t level;
		uint8_t mode;

	public:
		Audio();
		~Audio();
		inline uint8_t &getLevel() {return (this->level);};
		inline uint8_t &getMode() {return (this->mode);};

};

#endif
