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
		freq_plot.plot<double_t>(b_freq_mag);	
	}
}


void Signal::pad(int padded)
{
	ns_padded = padded;	
	
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

