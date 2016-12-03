#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <iostream>
#include <fftw3.h>
#include "taper.hpp"
#include "plot.hpp"

enum Domain {TIME, FREQUENCY};

class Signal
{
	private:
		double* b_time;	
		double* b_freq_mag;		
		fftw_complex* b_freq;
		
		int n_samples;
		int ns_padded;
		int sample_rate;
		
		Taper taper;
		GNUPlot time_plot;
		GNUPlot freq_plot;
		
	public:
		Signal(void);
		
		void zeroPad(int ns_zero_pad, Domain signal_domain);
		void applyTaper(int num_samples, Domain signal_domain);
		void conjugate(void);		
		void plot(Domain signal_domain);
		
		void setNumSamples(int num_samples){n_samples = num_samples;}
		void setNumPadded(int num_padded){ns_padded = num_padded;}
		void setTaper(TaperFunction Taper){taper.setFunction(Taper);}
		void setTimeBuffer(double* buffer){b_time = buffer;}
		
		//fftw_complex getFreqSample(int sample_num){return b_freq[sample_num];}
};


#endif
