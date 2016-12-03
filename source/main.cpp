#include "generator.hpp"
#include "transformer.hpp"
#include "recorder.hpp"
#include "taper.hpp"
#include "filter.hpp"

#define VERSION "2.0.0"

void splash(void);
void record(Recorder &recorder, int duration);

int main()
{
	Recorder word;
	Recorder sentence; 	
	Generator wavegen;		
	Transformer wordTransform;	
	Transformer sentenceTransform;
	Transformer resultTransform;
	Filter filter;	
	
	splash();
	
	wavegen.init(2, 40e3);
	
	wavegen.chirp(2000, 3, 1e3, 1e3);	
	wavegen.play();		
	record(word, 5);	
	
	wavegen.chirp(2000, 3, 0.9e3, 1e3);
	wavegen.play();		
	record(sentence, 5);
	
	int ns_padded = resultTransform.nextPowTwo(word.getNumSamples() + sentence.getNumSamples() - 1);
	
	wordTransform.init(word.getNumSamples(), ns_padded, UNIFORM);
	wordTransform.loadTime(word.getBuffer());
	wordTransform.forward();
	//wordTransform.plot(TIME);
	wordTransform.plot(FREQUENCY);
	
	sentenceTransform.init(sentence.getNumSamples(), ns_padded, HAMMING);
	sentenceTransform.loadTime(sentence.getBuffer());
	sentenceTransform.forward();	
	
	filter.matched(ns_padded, wordTransform.getFreq(), sentenceTransform.getFreq());
	
	resultTransform.init(ns_padded, ns_padded, UNIFORM);	
	resultTransform.loadFreq(filter.getResult());
	resultTransform.inverse();
	resultTransform.plot(TIME);
	
    return 0;
}


void record(Recorder &recorder, int duration)
{
	sf::Clock clock;
	
	clock.restart();	
	recorder.start();
	
	//std::cout << "Please speak slowly and clearly." << std::endl;
	
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
