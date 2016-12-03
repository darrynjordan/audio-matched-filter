#include "transformer.hpp"


Transformer::Transformer(void)
{
	
}


void Transformer::init(int num_samples, int padded, TaperFunction taperFunction)
{
	n_samples = num_samples;
	ns_padded = padded;

	taper.setFunction(taperFunction);
	taper.generate(n_samples);
	
	timePlot.init(ns_padded, "time-domain", false);
	freqPlot.init(ns_padded, "freq-domain", false);
	
	b_time     = (double*)malloc(ns_padded*sizeof(double));
	b_freq_mag = (double*)malloc(ns_padded*sizeof(double));
	b_freq     = (fftw_complex*)malloc(ns_padded*sizeof(fftw_complex));		
	
	memset(b_time, 0, ns_padded*sizeof(double));
	memset(b_freq_mag, 0, ns_padded*sizeof(double));
	memset(b_freq, 0, ns_padded*sizeof(fftw_complex));
}


void Transformer::loadTime(int16_t* buffer)
{
	for (int i = 0; i < n_samples; i++)
	{
		b_time[i] = (double)(buffer[i]*taper.getCoefficient(i));
	}	
}

void Transformer::loadFreq(fftw_complex* buffer)
{
	for (int i = 0; i < n_samples; i++)
	{
		b_freq[i][0] = buffer[i][0]*taper.getCoefficient(i);
		b_freq[i][1] = buffer[i][1]*taper.getCoefficient(i);
		
		b_freq_mag[i] = magnitude(b_freq[i]);
	}	
}


void Transformer::forward(void)
{
	fftw_plan plan = fftw_plan_dft_r2c_1d(ns_padded, b_time, b_freq, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);
	
	for (int i = 0; i < ns_padded; i++)
	{
		b_freq_mag[i] = magnitude(b_freq[i]);
	}		
}


void Transformer::inverse(void)
{
	fftw_plan plan = fftw_plan_dft_c2r_1d(ns_padded, b_freq, b_time, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);	
}


void Transformer::plot(SignalDomain Domain)
{
	if (Domain == TIME)
		timePlot.plot<double_t>(b_time);
	else if (Domain == FREQUENCY)
		freqPlot.plot<double_t>(b_freq_mag);	
}

