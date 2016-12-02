#ifndef PLOT_H
#define PLOT_H

#include <stdint.h>
#include <fstream>
#include <sstream> 

template <typename T> 
class GNUPlot 
{
	private:
		bool is_shift;
		int n_samples;
		const char* title;
		const char* x_label;
		const char* y_label;	
		
	public:
		GNUPlot(){title = "No Title"; x_label = "No Label"; y_label = "No Label";}

		void init(int num_samples, const char* Title, bool is_fft_shift = false)
		{
			title = Title;
			n_samples = num_samples; 
			is_shift = is_fft_shift;
		}
		
		void plot(T* buf_samples)
		{	
			FILE *gnuPipe = popen("gnuplot", "w");			
			char command[50];	
			
			std::stringstream ss;
			
			//setup gnuplot
			fputs("set terminal png enhanced font 'Script,12' linewidth 0.3 \n", gnuPipe);
			
			sprintf(command, "set title '%s' \n", title);
			fputs(command, gnuPipe);
			
			sprintf(command, "set output '%s.png' \n", title);
			fputs(command, gnuPipe);
			
			sprintf(command, "set xlabel '%s' \n", x_label);
			fputs(command, gnuPipe);
			
			sprintf(command, "set ylabel '%s' \n", y_label);
			fputs(command, gnuPipe);	
			
			fputs("", gnuPipe);
			
			fputs("plot '-' using 1:2 lt rgb 'blue' with lines notitle\n", gnuPipe);
			
			//write data to pipe
			for (int i = 0; i < n_samples; i++) 
			{
				//ss << i << " " << buf_samples[i] << "\n";
				//fprintf(gnuPipe, "%s", ss.str().c_str());
				
				fprintf(gnuPipe, "%i %f\n", i, buf_samples[i]);
			}
			
			//close gnuplot pipe
			fputs("e\n", gnuPipe);
			pclose(gnuPipe);	
			
			//print completion message
			sprintf(command, "%s", title);	
		}
		
		//void plot(int16_t *buf_samples, int num_samples);
		//void plot(double *buf_samples, int num_samples);
		//void plot(fftw_complex* buf_samples, int num_samples);
		
		void setTitle(const char *Title){title = Title;}
        const char *getTitle(void){return title;}   
        
        void setXLabel(const char *Label){x_label = Label;}
        const char *getXLabel(void){return x_label;}
        
        void setYLabel(const char *Label){y_label = Label;}
        const char *getYLabel(void){return y_label;}  		
};


#endif
