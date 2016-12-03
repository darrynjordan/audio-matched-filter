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
		double* b_time;	
		double* b_freq_mag;		
		fftw_complex* b_freq;			
		
		int n_samples;
		int ns_padded;
		
		Taper taper;
		fftw_plan plan;	
		Signal signal;   //TODO implement 
	
	public: 
		Transformer(void);
		void init(int num_samples, int padded, TaperFunction taperFunction);
		void forward(void);
		void inverse(void);
		void loadTime(int16_t* buffer);
		void loadFreq(fftw_complex* buffer);		
		
		double* getTime(void){return b_time;}
		fftw_complex* getFreq(void){return b_freq;}
		
		double magnitude(fftw_complex complex_number){return sqrt(pow(complex_number[0], 2) + pow(complex_number[1], 2));}
		int nextPowTwo(float value){return (pow(2, ceil(log(value)/log(2))));}
};

#endif
