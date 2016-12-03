#ifndef FILTER_HPP
#define FILTER_HPP

#include <fftw3.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include "plot.hpp"
#include "signal.hpp"

class Filter
{
	private:	
		fftw_complex* b_filtered;	
		double* b_filtered_mag;
		
		int ns_padded;
	
	public: 
		Filter(void);		
		void pad(Signal& signal_1, Signal& signal_2);	
		void matched(fftw_complex* b_ref, fftw_complex* b_raw);
		fftw_complex* getResult(void){return b_filtered;}
		
		int nextPowTwo(float value){return (pow(2, ceil(log(value)/log(2))));}
};

#endif
