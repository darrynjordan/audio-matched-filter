#include "filter.hpp"

Filter::Filter(void)
{
	
}


void Filter::matched(Signal& ref, Signal& raw, Signal& result)
{	
	fftw_complex* b_raw = raw.getFreqBuffer();
	fftw_complex* b_ref = ref.getFreqBuffer();	
	
	fftw_complex* b_filtered = (fftw_complex*)calloc(ns_padded, sizeof(fftw_complex));	
	
	for (int i = 0; i < ns_padded; i++)
	{			
		//conjugation
		b_ref[i][1] = -1*b_ref[i][1];
		
		//complex multiplication
		b_filtered[i][0] = b_ref[i][0]*b_raw[i][0] - b_ref[i][1]*b_raw[i][1];
		b_filtered[i][1] = b_ref[i][0]*b_raw[i][1] + b_ref[i][1]*b_raw[i][0];		
	}
	
	result.setFreqBuffer(b_filtered);
}


void Filter::pad(Signal& signal_1, Signal& signal_2)
{
	ns_padded = nextPowTwo(signal_1.getNumSamples() + signal_2.getNumSamples() - 1);
	signal_1.pad(ns_padded);
	signal_2.pad(ns_padded);	
}
