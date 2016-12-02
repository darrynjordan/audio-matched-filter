#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP

#include <fftw3.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SFML/Audio.hpp>
#include "taper.hpp"

using namespace std;

enum plotType {NORMAL, FFT_SHIFT};
enum plotStyle {AMPLITUDE, IQ};

class SpectrumAnalyzer
{
	private:
		double* b_samples;	
		fftw_complex* b_spectrum;	
		
		int n_samples;
		fftw_plan spectrumPlan;		
		Taper taper;
	
	public: 
		SpectrumAnalyzer(void);
		void init(int num_samples, TaperFunction taperFunction);
		void generateSpectrum(void);
		void loadBuffer(int16_t* buf_samples);
		void plotSpectrum(char const *plotTitle, plotType type = FFT_SHIFT, plotStyle style = AMPLITUDE);	
		void plotBuffer(char const *plotTitle);
};

#endif
