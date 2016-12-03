#ifndef RECORDER_HPP
#define RECORDER_HPP

#include <iostream>
#include <string.h>
#include <algorithm>
#include <SFML/Audio.hpp>
#include "signal.hpp"

class Recorder
{
	private:
		sf::SoundBufferRecorder recordingBuffer;
		sf::SoundBuffer raw_buffer;		
		sf::Clock clock;
		double* b_samples;
		bool is_save_audio;		
		
	public:
		Recorder(void);
		void record(Signal& signal, double duration);		
		void setSaveAudio(bool Save){is_save_audio = Save;}		
};


#endif
