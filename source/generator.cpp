#include "generator.hpp"


Generator::Generator(void)
{

}


void Generator::init(int Channels, int SampleRate)
{
	channels = Channels;
	cout << "Channels: " << channels << endl;
	sampleRate = SampleRate;
	cout << "Sample rate: " << sampleRate << " [samples/s]" << endl;
	cout << endl;
}


void Generator::play(void)
{
 	sound.setBuffer(buffer);
	sound.play();
}


void Generator::chirp(float amplitude, float duration, float centerFrequency, float bandwidth)
{
	float pi = acos(-1.0);
	float chirpRate  = bandwidth/duration;
	int n_samples = duration*sampleRate;
	
	b_samples = (int16_t*)malloc(n_samples*sizeof(int16_t));
	
	cout << "Chirp Parameters:" << endl;
	
	for (int i = 0; i < n_samples; i++)
	{		
		float t = i*(duration/(duration*sampleRate));
		b_samples[i] = amplitude*cos(2*pi*(centerFrequency)*t + pi*chirpRate*pow(t,2)); 				
	}
	
	buffer.loadFromSamples(&b_samples[0], n_samples, channels, sampleRate);
	
	if (is_save_audio)
	{
		buffer.saveToFile("transmitted_signal.ogg");
		cout << "Saved: transmitted_signal.ogg" << endl;
	}
	
	cout << "amplitude: " << amplitude << endl;
	cout << "duration: " << duration << " [s]" << endl;
	cout << "center frequency: " << centerFrequency << " [Hz]" << endl;
	cout << "bandwidth: " << bandwidth << " [Hz]" << endl;
	
}


void Generator::tone(float amplitude, float duration, float frequency)
{
	float pi = acos(-1.0);
	int n_samples = duration*sampleRate;
	
	b_samples = (int16_t*)malloc(n_samples*sizeof(int16_t));
		
	for (int i = 0; i < n_samples; i++)
	{		
		float t = i*(duration/(duration*sampleRate));
		b_samples[i] = amplitude*cos(2*pi*frequency*t); 
	}
	
	buffer.loadFromSamples(&b_samples[0], n_samples, channels, sampleRate);
	
}

void Generator::file(char* fileName)
{
	if (!buffer.loadFromFile(fileName))
        exit(0);
}


int16_t* Generator::getSamples(void)
{
	return b_samples;
}


