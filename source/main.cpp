#include "signal_generator.hpp"
#include "transformer.hpp"
#include "recorder.hpp"
#include "taper.hpp"

#define VERSION "1.1.0"

void splash(void);
void record(Recorder &recorder, int duration);

int main()
{
	Recorder word;
	Recorder sentence; 			
	Transformer transformer;		
	
	splash();
	
	record(word, 3);		
	transformer.init(word.getNumSamples(), HAMMING);
	transformer.loadBuffer(word.getBuffer());
	transformer.computeSpectrum();
	
	record(sentence, 6);		
	transformer.init(sentence.getNumSamples(), HAMMING);
	transformer.loadBuffer(sentence.getBuffer());
	transformer.computeSpectrum();
	
    return 0;
}


void record(Recorder &recorder, int duration)
{
	sf::Clock clock;
	
	clock.restart();	
	recorder.start();
	
	std::cout << "Please speak slowly and clearly." << std::endl;
	
	while (clock.getElapsedTime() < sf::seconds(duration));
	//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	
	recorder.stop();	
}


void splash(void)
{
	system("clear");
    printf("Word-Peak v%s\n", VERSION);
    printf("----------------\n");
}
