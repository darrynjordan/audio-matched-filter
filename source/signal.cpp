#include "signal.hpp"


Signal::Signal(void)
{
	
}


void Signal::plot(int num_samples, Domain domain)
{		
	if (domain == TIME)
	{
		time_plot.init(num_samples, "time-domain", false);
		time_plot.plot<double_t>(b_time);
	}
	else if (domain == FREQUENCY)
	{
		freq_plot.init(num_samples, "freq-domain", false);
		
		double* b_mag = (double*)calloc(num_samples, sizeof(double));
		
		for (int i = 0; i < num_samples; i++)
		{
			b_mag[i] = magnitude(b_freq[i]);
		}
		
		freq_plot.plot<double_t>(b_mag);	
	}
}


void Signal::pad(int padded)
{
	ns_padded = padded;	
	ns_spectrum = ns_padded/2 + 1;
	
	b_time = (double*)realloc(b_time, ns_padded*sizeof(double));
	memset(b_time + n_samples, 0, ns_padded - n_samples);	
}


void Signal::window(TaperFunction function, Domain domain)
{
	taper.setFunction(function);
	taper.generate(n_samples);
	
	for (int i = 0; i < n_samples; i++)
	{
		b_time[i] = (double)(b_time[i]*taper.getCoefficient(i));
	}	
}


void Signal::forward(int num_samples)
{	
	b_freq = (fftw_complex*)calloc(num_samples, sizeof(fftw_complex));
	
	fftw_plan plan = fftw_plan_dft_r2c_1d(num_samples, b_time, b_freq, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);	
}


void Signal::inverse(int num_samples)
{
	b_time = (double*)calloc(num_samples, sizeof(double));
	
	fftw_plan plan = fftw_plan_dft_c2r_1d(num_samples, b_freq, b_time, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);	
}


void Signal::saveAudio(void)
{
	b_sound.saveToFile("generated_waveform.ogg");
	std::cout << "generated_waveform.ogg" << std::endl;
}


void Signal::play(void)
{
 	// array type conversion
	int16_t* b_play = (int16_t*)calloc(n_samples, sizeof(int16_t));
    std::copy(b_time, b_time + n_samples, b_play);
 	
 	b_sound.loadFromSamples(b_play, n_samples, n_channels, sample_rate);
 	sound.setBuffer(b_sound);
	sound.play();
}

