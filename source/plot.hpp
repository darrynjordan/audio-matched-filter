#ifndef PLOT_H
#define PLOT_H

#include <stdint.h>
#include <fstream>
#include <sstream> 
#include <fftw3.h>
#include <typeinfo>
#include <math.h>
#include <iostream>

class GNUPlot 
{
	private:
		bool is_shift;
		int n_samples;
		const char* title;
		const char* x_label;
		const char* y_label;	
		
	public:
		GNUPlot(void);		

		void init(int num_samples, const char* Title, bool is_fft_shift = false);
		
		void setTitle(const char *Title){title = Title;}
        const char *getTitle(void){return title;}   
        
        void setXLabel(const char *Label){x_label = Label;}
        const char *getXLabel(void){return x_label;}
        
        void setYLabel(const char *Label){y_label = Label;}
        const char *getYLabel(void){return y_label;} 
		
		template <typename T> 
		void plot(T* buf_samples)
		{	
			std::stringstream ss;			
			ss << title << ".dat";
			
			//Create file with numerical data
			std::fstream fp(ss.str(), std::fstream::out); 
			
			if(fp.is_open()) 
			{				
				for (int i = 0; i < n_samples; i++) 
				{	
					double time = i/pow(2, 15);
					fp << time << " " << buf_samples[i] << "\n";
				}
			}
			
			fp.close();
			
			ss.str("");			
			ss << title << ".cmd";
			
			//Create Command file
			fp.open(ss.str(), std::fstream::out);
			
			if(fp.is_open()) 
			{
				fp 	<< "set terminal qt persist enhanced font 'Script,12'\n";
				fp	<< "set title '" << title << "'\n";
				//fp	<< "set output '" << title << ".png' \n";
				fp	<< "set xlabel '" << x_label << "'\n";
				fp	<< "set ylabel '" << y_label << "'\n";
				fp	<< "plot '" << title << ".dat' using 1:2 lt rgb 'blue' with lines notitle\n";
			}
			
			fp.close();		
			
			ss.str("");			
			ss << "gnuplot " << title << ".cmd";
			
			system(ss.str().c_str());	
		}        
};

#endif
