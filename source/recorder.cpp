#include "recorder.hpp"


Recorder::Recorder(void)
{
	initialize();
}


void Recorder::initialize(void)
{
	if (!sf::SoundBufferRecorder::isAvailable())
	{
		cout << "error: audio capture is not available on this system" << endl;
	}
}


void Recorder::start(void)
{
	recordingBuffer.start();
	cout << "Recording started..." << endl;
}


void Recorder::stop(void)
{
	recordingBuffer.stop();
	cout << "Recording stopped!" << endl;
	
	buffer = recordingBuffer.getBuffer();
	numSamples = buffer.getSampleCount();
	samples = (int16_t*)buffer.getSamples();
	buffer.saveToFile("received_signal.ogg");	
}


int Recorder::getNumSamples(void)
{
	return numSamples;
}


int16_t* Recorder::getSamples(void)
{
	return samples;
}



