#include "taper.hpp"


Taper::Taper(void)
{
	
}

float Taper::getCoefficient(int sampleNumber)
{
	return taper[sampleNumber];
}


void Taper::generate(int num_samples)
{
    n_samples = num_samples;
    
    taper = (float*)malloc(n_samples*sizeof(float));
    
    const double pi = 3.1415926;    

	for (int i = 0; i < n_samples; i++)
	{
        float common = (2*pi*i)/(n_samples - 1);
        
        switch(function)
		{
			case HANNING  : taper[i] = 0.50 - 0.50*cos(common); break;
			case HAMMING  : taper[i] = 0.54 - 0.46*cos(common); break;
			case BLACKMAN : taper[i] = 0.42659 - 0.49656*cos(common) + 0.076849*cos(2*common); break;
			case UNIFORM  : taper[i] = 1;
		}	
	}		
}


double Taper::sinc(double x)
{
   if (x == 0) return 1;
   return sin(x)/x;
}
