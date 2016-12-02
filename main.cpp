#include "source/includes.hpp"
#include <cmath>

#define CHANNELS 			1
#define SAMPLE_RATE 		44100
#define AMPLITUDE			5000
#define DURATION			3
#define CENTER_FREQUENCY 	0
#define	BANDWIDTH			5000

#define RECORDING_PERIOD 	3

int main()
{
	SignalGenerator signalGenerator;
	SpectrumAnalyzer spectrumAnalyzer;
	Recorder recorder; 
	
	sf::Clock clock;
	
	signalGenerator.setAudioParameters(CHANNELS, SAMPLE_RATE);
	signalGenerator.generateChirp(AMPLITUDE, DURATION, CENTER_FREQUENCY, BANDWIDTH);
	
	spectrumAnalyzer.allocateMemory(DURATION*SAMPLE_RATE);
	spectrumAnalyzer.loadSamples(signalGenerator.getSamples());
	spectrumAnalyzer.generateSpectrum();
	spectrumAnalyzer.gnuPlot("Tx Frequency Plot");
	
	clock.restart();
	
	recorder.start();
	signalGenerator.play();
	
	while (clock.getElapsedTime() < sf::seconds(RECORDING_PERIOD))
	{
		std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	}
	
	recorder.stop();
	
	spectrumAnalyzer.allocateMemory(recorder.getNumSamples());
	spectrumAnalyzer.loadSamples(recorder.getSamples());
	spectrumAnalyzer.generateSpectrum();
	spectrumAnalyzer.gnuPlot("Rx Frequency Plot");	
	
    return 0;
}
