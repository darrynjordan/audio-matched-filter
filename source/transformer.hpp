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
		double* b_samples;			
		fftw_complex* b_spectrum;	
		double* b_spectrum_mag;
		
		int n_samples;
		int ns_spectrum;
		
		Taper taper;
		fftw_plan spectrumPlan;	
		
		GNUPlot timePlot;
		GNUPlot freqPlot;
	
	public: 
		Transformer(void);
		void init(int num_samples, TaperFunction taperFunction);
		void computeSpectrum(void);
		void loadBuffer(int16_t* buf_samples);	
		void plotSignal(SignalDomain Domain);
};

#endif
