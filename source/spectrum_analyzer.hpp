#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP

#include <fftw3.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SFML/Audio.hpp>

using namespace std;

enum plotType {NORMAL, FFT_SHIFT};
enum plotStyle {AMPLITUDE, IQ};

class SpectrumAnalyzer
{
	private:
		double *signal;	
		fftw_complex *spectrum;	
		
		int numSamples;
		fftw_plan spectrumPlan;		
	
	public: 
		SpectrumAnalyzer(void);
		void allocateMemory(int sa_numSamples);
		void generateSpectrum(void);
		void loadSamples(int16_t* samples);
		void gnuPlot(char const *plotTitle, plotType type = FFT_SHIFT, plotStyle style = AMPLITUDE);	
};

#endif
