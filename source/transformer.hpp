#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include <fftw3.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SFML/Audio.hpp>
#include "taper.hpp"
#include "plot.hpp"
#include "signal.hpp"

class Transformer
{
	private:	
		fftw_plan plan;	
	
	public: 
		Transformer(void);

		void forward(Signal& signal);
		void inverse(Signal& signal);
		
		double magnitude(fftw_complex complex_number){return sqrt(pow(complex_number[0], 2) + pow(complex_number[1], 2));}		
};

#endif
