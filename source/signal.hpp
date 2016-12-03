#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <string.h>
#include <iostream>

#include <fftw3.h>
#include <SFML/Audio.hpp>

#include "taper.hpp"
#include "plot.hpp"

enum Domain {TIME, FREQUENCY};

class Signal
{
	private:
		double* b_time;				
		fftw_complex* b_freq;
		
		int n_samples;
		int ns_padded;
		int ns_spectrum;			
		int n_channels;
		int sample_rate;		
		bool is_standard;
		
		double duration;
		double amplitude;		
		
		Taper taper;
		GNUPlot time_plot;
		GNUPlot freq_plot;
		
		sf::Sound sound;
	    sf::SoundBuffer b_sound;
		
	public:
		Signal(void);
		
		void pad(int padded);
		void window(TaperFunction function, Domain domain);
		void conjugate(void);		
		void forward(int num_samples);
		void inverse(int num_samples);
		void plot(int num_samples, Domain domain);
		void play(void);
		void saveAudio(void);
		
		void setAmplitude(int amp){amplitude = amp;}
		void setChannels(int num_channels){n_channels = num_channels;}
		void setSampleRate(double rate){sample_rate = rate;}
		void setDuration(double length){duration = length;}
		void setNumSamples(int num_samples){n_samples = num_samples;}
		void setNumPadded(int num_padded){ns_padded = num_padded;}
		void setTimeBuffer(double* buffer){b_time = buffer;}	
		void setIsStandard(bool standard){is_standard = standard;}
		
		int getNumSamples(void){return n_samples;}	
		int getNumPadded(void){return ns_padded;}
		int getNumSpectrum(void){return ns_spectrum;}
		double getDuration(void){return duration;}	
		double getSampleRate(void){return sample_rate;}	
		
		double* getTimeBuffer(void){return b_time;}
		fftw_complex* getFreqBuffer(void){return b_freq;}
		
		double magnitude(fftw_complex complex_number){return sqrt(pow(complex_number[0], 2) + pow(complex_number[1], 2));}
};


#endif
