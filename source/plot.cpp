#include "plot.hpp"


GNUPlot::GNUPlot(void)
{
	title = "No Title"; 
	x_label = "No Label"; 
	y_label = "No Label";
}


void GNUPlot::init(int num_samples, const char* Title, bool is_fft_shift)
{
	title = Title;
	n_samples = num_samples; 
	is_shift = is_fft_shift;
}
