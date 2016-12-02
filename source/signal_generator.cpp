#include "signal_generator.hpp"


SignalGenerator::SignalGenerator(void)
{

}


void SignalGenerator::setAudioParameters(int sg_channels, int sg_sampleRate)
{
	cout << "Audio Parameters:" << endl;
	channels = sg_channels;
	cout << "channels: " << channels << endl;
	sampleRate = sg_sampleRate;
	cout << "sample rate: " << sampleRate << " [samples/s]" << endl;
	cout << endl;
}


void SignalGenerator::play(void)
{
 	sound.setBuffer(buffer);
	sound.play();
}


void SignalGenerator::generateChirp(float amplitude, float duration, float centerFrequency, float bandwidth)
{
	float pi = acos(-1.0);
	float chirpRate  = bandwidth/duration;
	int numSamples = duration*sampleRate;
	
	samples = (int16_t*)malloc(numSamples*sizeof(int16_t));
	
	cout << "Chirp Parameters:" << endl;
		
	for (int i = 0; i < numSamples; i++)
	{		
		float t = i*(duration/(duration*sampleRate));
		float sample = amplitude*cos(2*pi*centerFrequency*t + pi*chirpRate*pow(t,2)); 
		samples[i] = (sample);		
	}
	
	buffer.loadFromSamples(&samples[0], numSamples, channels, sampleRate);
	
	buffer.saveToFile("transmitted_signal.ogg");
	
	cout << "amplitude: " << amplitude << endl;
	cout << "duration: " << duration << " [s]" << endl;
	cout << "center frequency: " << centerFrequency << " [Hz]" << endl;
	cout << "bandwidth: " << bandwidth << " [Hz]" << endl;
	
}


void SignalGenerator::generateTone(float amplitude, float duration, float frequency)
{
	float pi = acos(-1.0);
	int numSamples = duration*sampleRate;
	
	samples = (int16_t*)malloc(numSamples*sizeof(int16_t));
		
	for (int i = 0; i < numSamples; i++)
	{		
		float t = i*(duration/(duration*sampleRate));
		float sample = amplitude*cos(2*pi*frequency*t); 
		samples[i] = (sample);	
	}
	
	buffer.loadFromSamples(&samples[0], numSamples, channels, sampleRate);
	
}

void SignalGenerator::loadFile(char* fileName)
{
	if (!buffer.loadFromFile(fileName))
        exit(0);
}


int16_t* SignalGenerator::getSamples(void)
{
	return samples;
}


