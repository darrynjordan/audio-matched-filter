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

enum SignalDomain {TIME, FREQUENCY};

class Transformer
{
	private:
		double* b_time;			
		fftw_complex* b_freq;	
		double* b_freq_mag;
		
		int n_samples;
		
		Taper taper;
		fftw_plan plan;	
		
		GNUPlot timePlot;
		GNUPlot freqPlot;
	
	public: 
		Transformer(void);
		void init(int num_samples, TaperFunction taperFunction);
		void forward(void);
		void inverse(void);
		void loadTime(int16_t* buffer);
		void loadFreq(fftw_complex* buffer);	
		void plot(SignalDomain Domain);
		
		double magnitude(fftw_complex complex_number){return sqrt(pow(complex_number[0], 2) + pow(complex_number[1], 2));}
};

#endif
