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
		double sample_rate;
		double duration;
		
		Taper taper;
		GNUPlot time_plot;
		GNUPlot freq_plot;
		
	public:
		Signal(void);
		
		void zeroPad(int ns_zero_pad, Domain signal_domain);
		void applyTaper(int num_samples, Domain signal_domain);
		void conjugate(void);		
		void plot(Domain signal_domain);
		
		void setSampleRate(double rate){sample_rate = rate;}
		void setDuration(double length){duration = length;}
		void setNumSamples(int num_samples){n_samples = num_samples;}
		void setNumPadded(int num_padded){ns_padded = num_padded;}
		void setTaper(TaperFunction function){taper.setFunction(function);}
		void setTimeBuffer(double* buffer){b_time = buffer;}	
		
		int getNumSamples(void){return n_samples;}	
		int getNumPadded(void){return ns_padded;}
		double getDuration(void){return duration;}	
		double getSampleRate(void){return sample_rate;}
		
		//fftw_complex getFreqSample(int sample_num){return b_freq[sample_num];}
};


#endif
