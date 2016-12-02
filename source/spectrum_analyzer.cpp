#include "spectrum_analyzer.hpp"


SpectrumAnalyzer::SpectrumAnalyzer(void)
{
	
}


void SpectrumAnalyzer::allocateMemory(int sa_numSamples)
{
	numSamples = sa_numSamples;
	signal = (double*)malloc(numSamples*sizeof(double));
	spectrum = (fftw_complex*)malloc(numSamples*sizeof(fftw_complex));
}


void SpectrumAnalyzer::loadSamples(int16_t* samples)
{
	for (int i = 0; i < numSamples; i++)
	{
		signal[i] = samples[i];
	}
}


void SpectrumAnalyzer::generateSpectrum(void)
{
	fftw_plan spectrumPlan = fftw_plan_dft_r2c_1d(numSamples, signal, spectrum, FFTW_ESTIMATE);
	fftw_execute(spectrumPlan);
}



void SpectrumAnalyzer::gnuPlot(char const *plotTitle, plotType type, plotStyle style)
{
	FILE *pipe_gp = popen("gnuplot", "w");	

	char writeTitle[100];
	strcpy(writeTitle, "set title '");
	strcat(writeTitle, plotTitle);
	strcat(writeTitle, "'\n");
	
	char writeFileName[100];
	strcpy(writeFileName, "set output '");
	strcat(writeFileName, plotTitle);
	strcat(writeFileName, ".eps'\n");	

	fputs("set terminal postscript eps enhanced color font 'Helvetica,20' linewidth 0.5\n", pipe_gp);
	fputs(writeTitle, pipe_gp);	
	//fputs("set yrange [-1:1] \n", pipe_gp);
	//fputs("set xrange[500:600] \n", pipe_gp);
	//fputs("set bmargin at screen 0.13 \n", pipe_gp);
	//fputs("set lmargin at screen 0.13 \n", pipe_gp);
	//fputs("set xtics ('0' 0, '10' 205, '20' 410, '30' 615, '40' 820, '50' 1024) \n", pipe_gp);
	//fputs("set xtics ('-500' 0, '-376' 32, '-252' 64, '-128' 96, '0' 128, '128' 160, '252' 192, '376' 224, '500' 255) \n", pipe_gp);
	//fputs("set xlabel 'Frequency [Hz]' \n", pipe_gp);
	//fputs("set xlabel 'Sample Number' \n", pipe_gp);
	//fputs("set ylabel 'Magnitude' \n", pipe_gp);
	fputs(writeFileName, pipe_gp);
	
	switch(type)
	{
		case NORMAL:
		{
			switch (style)
			{	
				case AMPLITUDE: 
				{
					fputs("plot '-' using 1:2 with lines notitle\n", pipe_gp);
					for (int i = 0; i < numSamples; i++) 
					{
						float magnitude = sqrt(pow(spectrum[i][0], 2) + pow(spectrum[i][1], 2));							
						fprintf(pipe_gp, "%i %f\n", i, magnitude);
					}
					break;
				}
				
				case IQ:
				{
					fputs("plot '-' title 'I Samples' with lines, '-' title 'Q Samples' with lines\n", pipe_gp);
					
					for (int i = 0; i < numSamples; i++) 
					{
						fprintf(pipe_gp, "%i %f\n", i, spectrum[i][0]);
					}
					fflush(pipe_gp);
					fprintf(pipe_gp, "e\n");						

					for (int i = 0; i < numSamples; i++) 
					{
						fprintf(pipe_gp, "%i %f\n", i, spectrum[i][1]);
					}
					break;
				}										
			}	
			break;
		}
		
		case FFT_SHIFT:
		{
			fputs("plot '-' using 1:2 with lines notitle\n", pipe_gp);
			for (int i = 0; i < numSamples; i++) 
			{
				if (i < (numSamples/2 + 1))
				{
					fprintf(pipe_gp, "%i %f\n", i, ((sqrt(spectrum[i + (numSamples/2 - 1)][0]*spectrum[i + (numSamples/2 - 1)][0] +
															 spectrum[i + (numSamples/2 - 1)][1]*spectrum[i + (numSamples/2 - 1)][1]))));
				}
				else
				{
					fprintf(pipe_gp, "%i %f\n", i, ((sqrt(spectrum[i - (numSamples/2 + 1)][0]*spectrum[i - (numSamples/2 + 1)][0] + 
															 spectrum[i - (numSamples/2 + 1)][1]*spectrum[i - (numSamples/2 + 1)][1]))));
				}
			}
			break;	
		}
	}	

	fputs("e\n", pipe_gp);
	pclose(pipe_gp);	
	
	char writeMessage[100];
	strcpy(writeMessage, "Generated Plot: ");
	strcat(writeMessage, plotTitle);		
}
