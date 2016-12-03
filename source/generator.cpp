#include "generator.hpp"


Generator::Generator(void)
{

}


void Generator::chirp(Signal& waveform, float amp, float duration, float center_freq, float bandwidth, int channels, int sample_rate)
{
	int n_samples = duration*sample_rate;
	double time = 0;
	double pi = acos(-1.0);	
	double chirp_rate  = bandwidth/duration;	
	
	double* b_chirp = (double*)malloc(n_samples*sizeof(double));
	
	for (int i = 0; i < n_samples; i++)
	{		
		time = (double)i/(double)sample_rate;
		b_chirp[i] = amp*cos(2*pi*(center_freq)*time + pi*chirp_rate*pow(time,2)); 				
	}		

	waveform.setIsStandard(true);
	waveform.setAmplitude(amp);
	waveform.setDuration(duration);
	waveform.setChannels(channels);
	waveform.setSampleRate(sample_rate);
	waveform.setNumSamples(n_samples);	
	waveform.setTimeBuffer(b_chirp);
}


void Generator::tone(Signal& waveform, float amp, float duration, float freq, int channels, int sample_rate)
{
	int n_samples = duration*sample_rate;
	double time = 0;
	double pi = acos(-1.0);	
	
	double* b_tone = (double*)malloc(n_samples*sizeof(double));
	
	for (int i = 0; i < n_samples; i++)
	{		
		time = (double)i/(double)sample_rate;
		b_tone[i] = amp*cos(2*pi*freq*time); 		
	}	
	
	waveform.setIsStandard(true);
	waveform.setAmplitude(amp);
	waveform.setDuration(duration);
	waveform.setChannels(channels);
	waveform.setSampleRate(sample_rate);
	waveform.setNumSamples(n_samples);	
	waveform.setTimeBuffer(b_tone);
}


/*
void Generator::load(char* fileName)
{
	if (!buffer.loadFromFile(fileName))
        exit(0);
}*/


