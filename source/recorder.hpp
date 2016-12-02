#ifndef RECORDER_HPP
#define RECORDER_HPP

#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

class Recorder
{
	private:
		sf::SoundBufferRecorder recordingBuffer;
		sf::SoundBuffer buffer;
		int16_t* b_samples;
		int n_samples;
		bool is_save_audio;
		
	public:
		Recorder(void);
		void start(void);
		void stop(void);
		int getNumSamples(void);
		int16_t* getBuffer(void);
		void setSaveAudio(bool Save){is_save_audio = Save;}
};


#endif
