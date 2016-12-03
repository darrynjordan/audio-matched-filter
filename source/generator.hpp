#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <cmath>
#include <stdint.h>
#include <iostream>

#include <SFML/Audio.hpp>

#include "signal.hpp"

class Generator
{

	public:
		Generator();
		
		void tone(Signal& waveform, float amp, float duration, float freq, int channels = 1, int sample_rate = 40e3);
		void chirp(Signal& waveform, float amp, float duration, float center_freq, float bandwidth, int channels = 1, int sample_rate = 40e3);		
		//void load(char* fileName);
};

#endif
