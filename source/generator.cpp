#include "generator.hpp"


Generator::Generator(void)
{

}


void Generator::init(int Channels, int SampleRate)
{
	channels = Channels;
	std::cout << "channels: \t" << channels << std::endl;
	dac_rate = SampleRate;
	std::cout << "dac_rate: \t" << dac_rate << "\t[Hz]" << std::endl;
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
	int n_samples = duration*dac_rate;
	
	b_samples = (int16_t*)malloc(n_samples*sizeof(int16_t));
	
	for (int i = 0; i < n_samples; i++)
	{		
		float t = i*(duration/(duration*dac_rate));
		b_samples[i] = amplitude*cos(2*pi*(centerFrequency)*t + pi*chirpRate*pow(t,2)); 				
	}
	
	buffer.loadFromSamples(&b_samples[0], n_samples, channels, dac_rate);
	
	if (is_save_audio)
	{
		buffer.saveToFile("generated_waveform.ogg");
		std::cout << "saved: \t\tgenerated_waveform.ogg" << std::endl;
	}
	
	std::cout << "amplitude: \t" << amplitude << std::endl;
	std::cout << "duration: \t" << duration << "\t[s]" << std::endl;
	std::cout << "center_freq: \t" << centerFrequency << "\t[Hz]" << std::endl;
	std::cout << "bandwidth: \t" << bandwidth << "\t[Hz]" << std::endl;	
}


void Generator::tone(float amplitude, float duration, float frequency)
{
	float pi = acos(-1.0);
	int n_samples = duration*dac_rate;
	
	b_samples = (int16_t*)malloc(n_samples*sizeof(int16_t));
		
	for (int i = 0; i < n_samples; i++)
	{		
		float t = i*(duration/(duration*dac_rate));
		b_samples[i] = amplitude*cos(2*pi*frequency*t); 
	}
	
	buffer.loadFromSamples(&b_samples[0], n_samples, channels, dac_rate);
	
}

void Generator::file(char* fileName)
{
	if (!buffer.loadFromFile(fileName))
        exit(0);
}


