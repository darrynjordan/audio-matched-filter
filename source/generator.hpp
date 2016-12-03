#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <SFML/Audio.hpp>
#include <cmath>
#include <stdint.h>
#include <iostream>

class Generator
{
	private:
	    sf::Sound sound;
	    sf::SoundBuffer buffer;
	    int16_t* b_samples;
	    int n_samples;
	    int channels;
	    int dac_rate;
	    bool is_save_audio;
		
	public:
		Generator(void);
		void init(int Channels, int SampleRate);
		void chirp(float amplitude, float duration, float centerFrequency, float bandwidth);
		void tone(float amplitude, float duration, float frequency);
		void file(char* fileName);
		void play(void);
		void setSaveAudio(bool Save){is_save_audio = Save;}
};

#endif
