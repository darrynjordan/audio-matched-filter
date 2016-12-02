#include "transformer.hpp"


Transformer::Transformer(void)
{
	
}


void Transformer::init(int num_samples, TaperFunction taperFunction)
{
	n_samples = num_samples;

	taper.setFunction(taperFunction);
	taper.generate(n_samples);
	
	timePlot.init(n_samples, "time-domain", false);
	freqPlot.init(n_samples, "freq-domain", false);
	
	b_time     = (double*)malloc(n_samples*sizeof(double));
	b_freq_mag = (double*)malloc(n_samples*sizeof(double));
	b_freq     = (fftw_complex*)malloc(n_samples*sizeof(fftw_complex));		
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
	fftw_plan plan = fftw_plan_dft_r2c_1d(n_samples, b_time, b_freq, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);
	
	for (int i = 0; i < n_samples; i++)
	{
		b_freq_mag[i] = magnitude(b_freq[i]);
	}		
}


void Transformer::inverse(void)
{
	fftw_plan plan = fftw_plan_dft_c2r_1d(n_samples, b_freq, b_time, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);	
}


void Transformer::plot(SignalDomain Domain)
{
	if (Domain == TIME)
		timePlot.plot<double_t>(b_time);
	else if (Domain == FREQUENCY)
		freqPlot.plot<double_t>(b_freq_mag);	
}

