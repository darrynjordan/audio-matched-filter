#ifndef FILTER_HPP
#define FILTER_HPP

#include <fftw3.h>
#include <math.h>
#include <iostream>
#include <string.h>

class Filter
{
	private:	
		fftw_complex* b_filtered;	
	
	public: 
		Filter(void);		
		fftw_complex* matched(int ns_padded, fftw_complex* b_ref, fftw_complex* b_raw);		
};

#endif
