#ifndef TAPER_HPP
#define TAPER_HPP

#include <iostream>
#include <math.h>

enum TaperFunction {HANNING, HAMMING, UNIFORM, BLACKMAN};

class Taper
{
	private:
		TaperFunction function;
		float* taper;	
		int n_samples;	
		
	public:		
		Taper(void);
		void setFunction(TaperFunction Function){function = Function;};
		int getNumSamples(void){return n_samples;};		
		void generate(int num_samples);
		float getCoefficient(int sampleNumber);
        double sinc(double x);
};

#endif
