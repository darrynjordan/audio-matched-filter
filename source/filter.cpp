#include "filter.hpp"

Filter::Filter(void)
{
	
}


fftw_complex* Filter::matched(int ns_padded, fftw_complex* b_ref, fftw_complex* b_raw)
{	
	b_filtered = (fftw_complex*)malloc(ns_padded*sizeof(fftw_complex));	
	memset(b_filtered, 0, ns_padded*sizeof(fftw_complex));
	
	for (int i = 0; i < ns_padded; i++)
	{			
		//conjugation
		b_ref[i][1] = -1*b_ref[i][1];
		
		//complex multiplication
		b_filtered[i][0] = b_ref[i][0]*b_raw[i][0] - b_ref[i][1]*b_raw[i][1];
		b_filtered[i][1] = b_ref[i][0]*b_raw[i][1] + b_ref[i][1]*b_raw[i][0];
	}
	
	return b_filtered;	
}

