#include "signal.hpp"


Signal::Signal(void)
{
	
}


void Signal::plot(Domain signal_domain)
{	
	
	time_plot.init(n_samples, "time-domain", false);
	freq_plot.init(n_samples, "freq-domain", false);
	
	if (signal_domain == TIME)
		time_plot.plot<double_t>(b_time);
	else if (signal_domain == FREQUENCY)
		freq_plot.plot<double_t>(b_freq_mag);	
}


