#include "spectrum_analyzer.hpp"


SpectrumAnalyzer::SpectrumAnalyzer(void)
{
	
}


void SpectrumAnalyzer::init(int num_samples, TaperFunction taperFunction)
{
	n_samples = num_samples;

	taper.setFunction(taperFunction);
	taper.generate(n_samples);
	
	p_word_time.init(n_samples, "Word - Time Domain", false);
	
	b_samples = (double*)malloc(n_samples*sizeof(double));
	b_spectrum = (fftw_complex*)malloc(n_samples*sizeof(fftw_complex));	
}


void SpectrumAnalyzer::loadBuffer(int16_t* buf_samples)
{
	for (int i = 0; i < n_samples; i++)
	{
		b_samples[i] = (double)(buf_samples[i]*taper.getCoefficient(i));
	}
	
	p_word_time.plot(b_samples);
}


void SpectrumAnalyzer::generateSpectrum(void)
{
	fftw_plan spectrumPlan = fftw_plan_dft_r2c_1d(n_samples, b_samples, b_spectrum, FFTW_ESTIMATE);
	fftw_execute(spectrumPlan);
}
