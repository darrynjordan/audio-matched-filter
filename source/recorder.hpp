#ifndef RECORDER_HPP
#define RECORDER_HPP

#include <iostream>
#include <SFML/Audio.hpp>
#include "signal.hpp"

class Recorder
{
	private:
		sf::SoundBufferRecorder recordingBuffer;
		sf::SoundBuffer raw_buffer;
		sf::Clock clock;
		int16_t* b_samples;
		int n_samples;
		bool is_save_audio;
		
		Signal signal;
		
	public:
		Recorder(void);
		void record(Signal rec_signal, int duration);

		void setSaveAudio(bool Save){is_save_audio = Save;}
};


#endif
