#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP

#include <fftw3.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SFML/Audio.hpp>
#include "taper.hpp"
#include "plot.hpp"

class SpectrumAnalyzer
{
	private:
		double* b_samples;	
		fftw_complex* b_spectrum;	
		double* b_spectrum_mag;
		
		int n_samples;
		fftw_plan spectrumPlan;		
		Taper taper;
		GNUPlot p_word_time;
		GNUPlot p_word_freq;
	
	public: 
		SpectrumAnalyzer(void);
		void init(int num_samples, TaperFunction taperFunction);
		void generateSpectrum(void);
		void loadBuffer(int16_t* buf_samples);		
};

#endif
