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
		int ns_padded;
		
	public: 
		Filter(void);		
		void pad(Signal& signal_1, Signal& signal_2);	
		void matched(Signal& ref, Signal& raw, Signal& result);
		
		int nextPowTwo(float value){return (pow(2, ceil(log(value)/log(2))));}
		double magnitude(fftw_complex complex_number){return sqrt(pow(complex_number[0], 2) + pow(complex_number[1], 2));}
};

#endif
