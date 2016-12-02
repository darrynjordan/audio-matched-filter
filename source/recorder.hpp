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
		int16_t* samples;
		int numSamples;
	public:
		Recorder(void);
		void initialize(void);
		void start(void);
		void stop(void);
		int getNumSamples(void);
		int16_t* getSamples(void);
};


#endif
