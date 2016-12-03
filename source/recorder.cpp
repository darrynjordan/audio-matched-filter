#include "recorder.hpp"


Recorder::Recorder(void)
{
	if (!sf::SoundBufferRecorder::isAvailable())
	{
		std::cout << "error: audio capture is not available on this system" << std::endl;
	}
}


void Recorder::record(Signal& signal, double duration)
{
	clock.restart();		
	
	recordingBuffer.start();
	std::cout << "recording started." << std::endl;
	
	//std::cout << "Please speak slowly and clearly." << std::endl;
	
	while (clock.getElapsedTime() < sf::seconds(duration));
	
	//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	
	recordingBuffer.stop();
	std::cout << "recording stopped." << std::endl;
	
	raw_buffer = recordingBuffer.getBuffer();
	
	signal.setNumSamples(raw_buffer.getSampleCount());	
	signal.setDuration(duration);
	signal.setSampleRate(signal.getNumSamples()/duration);

	// array type conversion
	b_samples = (double*)calloc(signal.getNumSamples(), sizeof(double));	
    std::copy(raw_buffer.getSamples(), raw_buffer.getSamples() + signal.getNumSamples(), b_samples);
    
	signal.setTimeBuffer(b_samples);
	
	if (is_save_audio)
	{
		raw_buffer.saveToFile("recorded_waveform.ogg");
		std::cout << "saved: \t\trecorded_waveform.ogg" << std::endl;
	}	
}



