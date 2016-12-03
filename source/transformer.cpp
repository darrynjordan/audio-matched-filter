#include "transformer.hpp"


Transformer::Transformer(void)
{
	
}


void Transformer::forward(Signal& signal)
{
	/*b_freq = (fftw_complex*)calloc(signal.getNumPadded()*sizeof(fftw_complex));		
	
	fftw_plan plan = fftw_plan_dft_r2c_1d(signal.getNumPadded(), b_time, b_freq, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);
	
	for (int i = 0; i < ns_padded; i++)
	{
		b_freq_mag[i] = magnitude(b_freq[i]);
	}*/
}


void Transformer::inverse(Signal& signal)
{
	/*fftw_plan plan = fftw_plan_dft_c2r_1d(ns_padded, b_freq, b_time, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);	*/
}



