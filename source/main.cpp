#include "generator.hpp"
#include "recorder.hpp"
#include "taper.hpp"
#include "filter.hpp"

#define VERSION "2.8.0"

void splash(void);

int main()
{	
	int ns_padded;
	
	Signal word;
	Signal sentence;
	Signal waveform;
	
	Filter filter;
	Recorder recorder;
	Generator generator;			
	
	splash();
	
	//generator.tone(waveform, 100, 1, 1e3);
	generator.chirp(waveform, 100, 1, 1e3, 1e3);
	waveform.forward(waveform.getNumSamples());
	waveform.plot(waveform.getNumSamples(), FREQUENCY);
	waveform.play();		
	
	recorder.setSaveAudio(false);
	
	recorder.record(word, 1);	
	recorder.record(sentence, 1);
	
	word.window(UNIFORM, TIME);
	filter.pad(word, sentence);		

	word.forward(word.getNumPadded());	
	sentence.forward(word.getNumPadded());	
	
	//filter.matched(ns_padded, wordTransform.getFreq(), sentenceTransform.getFreq());
	
    return EXIT_SUCCESS;
}



void splash(void)
{
	system("clear");
    printf("Word-Peak v%s\n", VERSION);
    printf("----------------\n");
}
