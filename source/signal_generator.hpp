#ifndef SIGNAL_GENERATOR_HPP
#define SIGNAL_GENERATOR_HPP

#include <SFML/Audio.hpp>
#include <cmath>
#include <stdint.h>
#include <iostream>

using namespace std;

class SignalGenerator
{
	private:
	    sf::Sound sound;
	    sf::SoundBuffer buffer;
	    int16_t* samples;
	    int channels;
	    int sampleRate;
		
	public:
		SignalGenerator(void);
		void setAudioParameters(int sg_channels, int sg_sampleRate);
		void generateChirp(float amplitude, float duration, float centerFrequency, float bandwidth);
		void generateTone(float amplitude, float duration, float frequency);
		void loadFile(char* fileName);
		void play(void);
		int16_t* getSamples(void);
};

#endif
