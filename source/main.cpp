#include "includes.hpp"

#define CHANNELS 			1
#define SAMPLE_RATE 		44100
#define AMPLITUDE			0.5

#define VERSION 			"1.0.0"

void splash(void);
void performRecording(Recorder *recorder, int duration);

int main()
{
	Recorder word;
	Recorder sentence; 			
	SpectrumAnalyzer spectrumAnalyzer;	
	
	splash();
	performRecording(&word, 3);	
	
	spectrumAnalyzer.init(word.getNumSamples(), HAMMING);
	spectrumAnalyzer.loadBuffer(word.getBuffer());
	spectrumAnalyzer.generateSpectrum();
	spectrumAnalyzer.plotSpectrum("Word Spectrum");	

	/*
	spectrumAnalyzer.allocateMemory(recorder.getNumSamples());
	spectrumAnalyzer.loadSamples(recorder.getSamples());
	spectrumAnalyzer.generateSpectrum();
	spectrumAnalyzer.gnuPlot("Rx Frequency Plot");	
	*/
	
    return 0;
}


void performRecording(Recorder *recorder, int duration)
{
	sf::Clock clock;
	
	clock.restart();	
	recorder->start();
	
	std::cout << "Please say a word clearly." << std::endl;
	
	while (clock.getElapsedTime() < sf::seconds(duration));
	//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	
	recorder->stop();	
}


void splash(void)
{
	system("clear");
    printf("Word-Peak v%s\n", VERSION);
    printf("------------------------------\n");
}
