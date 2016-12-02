#include "signal_generator.hpp"
#include "transformer.hpp"
#include "recorder.hpp"
#include "taper.hpp"
#include "filter.hpp"

#define VERSION "1.5.0"

void splash(void);
void record(Recorder &recorder, int duration);

int main()
{
	Recorder word;
	Recorder sentence; 			
	Transformer wordTransform;	
	Transformer sentenceTransform;
	Transformer resultTransform;
	Filter filter;	
	
	splash();
	
	record(word, 1);	
	record(sentence, 1);
	
	wordTransform.init(word.getNumSamples(), HAMMING);
	wordTransform.loadTime(word.getBuffer());
	wordTransform.forward();
	
	sentenceTransform.init(sentence.getNumSamples(), HAMMING);
	sentenceTransform.loadTime(sentence.getBuffer());
	sentenceTransform.forward();
	
	int ns_padded = resultTransform.nextPowTwo(word.getNumSamples() + sentence.getNumSamples() - 1);
	
	resultTransform.init(ns_padded, UNIFORM);
	resultTransform.loadFreq(filter.matched(ns_padded, wordTransform.getFreq(), sentenceTransform.getFreq()));
	resultTransform.inverse();
	resultTransform.plot(TIME);
	
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
