#include "generator.hpp"
#include "recorder.hpp"
#include "taper.hpp"
#include "filter.hpp"

#define VERSION "3.0.0"

void splash(void);

int main()
{	
	int ns_padded;
	
	Signal word;
	Signal sentence;
	Signal waveform;
	Signal result;
	
	Filter filter;
	Recorder recorder;
	Generator generator;			
	
	splash();
	
	generator.tone(waveform, 100, 7, 1e3);
	waveform.window(HAMMING, TIME);
	waveform.forward(waveform.getNumSamples());
	waveform.plot(waveform.getNumSamples(), TIME);	
	waveform.plot(waveform.getNumSamples(), FREQ);
	waveform.saveAudio();
	waveform.play();	
	
	recorder.record(word, 2);	
	word.plot(word.getNumSamples(), TIME);	
	
	waveform.play();
	
	recorder.record(sentence, 5);
	sentence.plot(sentence.getNumSamples(), TIME);
	
	word.window(HAMMING, TIME);
	word.plot(word.getNumSamples(), TIME);
	
	filter.pad(word, sentence);			
	word.plot(word.getNumPadded(), TIME);
	sentence.plot(sentence.getNumPadded(), TIME);

	word.forward(word.getNumPadded());	
	word.plot(word.getNumSpectrum(), FREQ);
	
	sentence.forward(word.getNumPadded());			
	sentence.plot(sentence.getNumSpectrum(), FREQ);
	
	filter.matched(word, sentence, result);
	result.plot(result.getNumPadded(), FREQ);
	
	result.inverse(result.getNumPadded());
	result.plot(result.getNumPadded(), TIME);
	
    return EXIT_SUCCESS;
}



void splash(void)
{
	system("clear");
    printf("Word-Peak v%s\n", VERSION);
    printf("----------------\n");
}
