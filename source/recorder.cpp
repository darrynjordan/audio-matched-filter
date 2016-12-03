#include "recorder.hpp"


Recorder::Recorder(void)
{
	if (!sf::SoundBufferRecorder::isAvailable())
	{
		std::cout << "error: audio capture is not available on this system" << std::endl;
	}
}


void Recorder::record(Signal rec_signal, int duration)
{
	signal = rec_signal;
	
	clock.restart();		
	
	recordingBuffer.start();
	std::cout << "Recording started." << std::endl;
	
	//std::cout << "Please speak slowly and clearly." << std::endl;
	
	while (clock.getElapsedTime() < sf::seconds(duration));
	
	//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	
	recordingBuffer.stop();
	std::cout << "Recording stopped." << std::endl;
	
	raw_buffer = recordingBuffer.getBuffer();
	
	signal.setNumSamples(raw_buffer.getSampleCount());
	signal.setTimeBuffer((double*)raw_buffer.getSamples());
	
	if (is_save_audio)
	{
		raw_buffer.saveToFile("recorded_signal.ogg");
		std::cout << "Saved: recorded_signal.ogg" << std::endl;
	}
	
	
	
}



