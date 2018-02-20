#ifndef AUDIO_H
# define AUDIO_H

# include <portaudio.h>
# include <cstdint>

# define AUDIO_C12_TYPE_SQUARE 1
# define AUDIO_C12_TYPE_SINE 2
# define AUDIO_C12_TYPE_TRIANGLE 3
# define AUDIO_C12_TYPE_SAW 4

class Audio
{

	private:
		PaStream *stream;
		uint8_t c12type;
		bool mute;

	public:
		Audio();
		~Audio();
		void start();
		inline uint8_t &getC12type() {return (c12type);};
		inline void setMute(bool mute) {this->mute = mute;};
		inline bool isMute() {return (this->mute);};

};

#endif
