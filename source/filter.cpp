#include "filter.hpp"

Filter::Filter(void)
{
	
}


void Filter::matched(fftw_complex* b_ref, fftw_complex* b_raw)
{	
	b_filtered = (fftw_complex*)malloc(ns_padded*sizeof(fftw_complex));	
	b_filtered_mag = (double*)malloc(ns_padded*sizeof(double));
	
	memset(b_filtered, 0, ns_padded*sizeof(fftw_complex));
	memset(b_filtered_mag, 0, ns_padded*sizeof(double));
	
	for (int i = 0; i < ns_padded; i++)
	{			
		//conjugation
		b_ref[i][1] = -1*b_ref[i][1];
		
		//complex multiplication
		b_filtered[i][0] = b_ref[i][0]*b_raw[i][0] - b_ref[i][1]*b_raw[i][1];
		b_filtered[i][1] = b_ref[i][0]*b_raw[i][1] + b_ref[i][1]*b_raw[i][0];
		
		b_filtered_mag[i] = sqrt(pow(b_filtered[i][0], 2) + pow(b_filtered[i][1], 2));
	}
}


void Filter::pad(Signal& signal_1, Signal& signal_2)
{
	ns_padded = nextPowTwo(signal_1.getNumSamples() + signal_2.getNumSamples() - 1);
	signal_1.pad(ns_padded);
	signal_2.pad(ns_padded);	
}
