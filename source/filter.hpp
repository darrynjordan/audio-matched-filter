#ifndef FILTER_HPP
#define FILTER_HPP

#include <fftw3.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include "plot.hpp"

class Filter
{
	private:	
		fftw_complex* b_filtered;	
		double* b_filtered_mag;
		GNUPlot resultPlot;
	
	public: 
		Filter(void);		
		void matched(int ns_padded, fftw_complex* b_ref, fftw_complex* b_raw);		
		void plot(void);
		fftw_complex* getResult(void){return b_filtered;}
};

#endif
