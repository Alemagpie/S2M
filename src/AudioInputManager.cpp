#include "AudioInputManager.h"

AudioInputManager::AudioInputManager() {
    options.flags = RTAUDIO_MINIMIZE_LATENCY;
    parameters.deviceId = adc.getDefaultInputDevice();  //This needs to change to be able to select the input
    std::cout << "Input device id: " << parameters.deviceId << std::endl;
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
}
 
//Opens and starts stream
void AudioInputManager::startInput(RtAudioCallback audioCallback, void *userData) {
    adc.openStream(NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, audioCallback, userData, &options);
    adc.startStream();
}

//Stops and closes stream
void AudioInputManager::stopInput() {
    adc.stopStream();
    if (adc.isStreamOpen()) {
        adc.closeStream();
    }
}