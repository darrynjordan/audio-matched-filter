#include "spectrum_analyzer.hpp"


SpectrumAnalyzer::SpectrumAnalyzer(void)
{
	
}


void SpectrumAnalyzer::init(int num_samples, TaperFunction taperFunction)
{
	n_samples = num_samples;
	ns_spectrum = n_samples/2 + 1;

	taper.setFunction(taperFunction);
	taper.generate(n_samples);
	
	timePlot.init(n_samples, "time-domain", false);
	freqPlot.init(ns_spectrum, "freq-domain", false);
	
	b_samples = (double*)malloc(n_samples*sizeof(double));
	b_spectrum = (fftw_complex*)malloc(n_samples*sizeof(fftw_complex));	
	b_spectrum_mag = (double*)malloc(ns_spectrum*sizeof(double));
}


void SpectrumAnalyzer::loadBuffer(int16_t* buf_samples)
{
	for (int i = 0; i < n_samples; i++)
	{
		b_samples[i] = (double)(buf_samples[i]*taper.getCoefficient(i));
	}
	
	timePlot.plot<double_t>(b_samples);
}


void SpectrumAnalyzer::generateSpectrum(void)
{
	fftw_plan spectrumPlan = fftw_plan_dft_r2c_1d(n_samples, b_samples, b_spectrum, FFTW_ESTIMATE);
	fftw_execute(spectrumPlan);
	
	for (int i = 0; i < ns_spectrum; i++)
	{
		b_spectrum_mag[i] = sqrt(pow(b_spectrum[i][0], 2) + pow(b_spectrum[i][1], 2));
	}	
	
	freqPlot.plot<double_t>(b_spectrum_mag);
}

