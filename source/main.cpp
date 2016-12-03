#include "generator.hpp"
#include "transformer.hpp"
#include "recorder.hpp"
#include "taper.hpp"
#include "filter.hpp"

#define VERSION "2.6.0"

void splash(void);

int main()
{	
	int ns_padded;
	
	Signal word;
	Signal sentence;
	
	Recorder recorder;
	Generator wavegen;		
	Transformer transformer;
	Filter filter;	
	
	splash();
	
	wavegen.setSaveAudio(false);
	wavegen.init(2, 40e3);	
	//wavegen.chirp(2000, 3, 1e3, 1e3);	
	wavegen.tone(2000, 2, 5);
	wavegen.play();		
	
	recorder.setSaveAudio(false);
	recorder.record(word, 3);	
	recorder.record(sentence, 1);
	
	word.window(HAMMING, TIME);
	filter.pad(word, sentence);	
	
	word.plot(word.getNumSamples(), TIME);
	
	transformer.forward(word);
	
	/*
	wordTransform.init(word.getNumSamples(), ns_padded, UNIFORM);
	wordTransform.loadTime(word.getBuffer());
	wordTransform.forward();
	
	sentenceTransform.init(sentence.getNumSamples(), ns_padded, HAMMING);
	sentenceTransform.loadTime(sentence.getBuffer());
	sentenceTransform.forward();	
	
	filter.matched(ns_padded, wordTransform.getFreq(), sentenceTransform.getFreq());
	
	resultTransform.init(ns_padded, ns_padded, UNIFORM);	
	resultTransform.loadFreq(filter.getResult());*/
	
    return EXIT_SUCCESS;
}



void splash(void)
{
	system("clear");
    printf("Word-Peak v%s\n", VERSION);
    printf("----------------\n");
}
