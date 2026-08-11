#include "AudioInputManager.h"

AudioInputManager::AudioInputManager() {
    options.flags = RTAUDIO_MINIMIZE_LATENCY;       
    parameters.deviceId = adc.getDefaultInputDevice();  
    std::cout << "Using API: " << RtAudio::getApiDisplayName(adc.getCurrentApi()) << "\n";
    unsigned int count = adc.getDeviceCount();
    std::cout << "Found " << count << " device(s). \n";
    std::vector<unsigned int> ids = adc.getDeviceIds();
    for(int i = 0; i < count; i++) {
        std::cout << "- Device with id " << ids[i] << ": " << adc.getDeviceInfo(ids[i]).name << "\n"; 
    }

    std::cout << "\n\n";

    parameters.nChannels = 1;
    parameters.firstChannel = 0;
}
 
//Opens and starts stream
void AudioInputManager::startInput(RtAudioCallback audioCallback, void *userData) {
    callback = audioCallback;
    data = userData;
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

void AudioInputManager::restartInput() {
    bool wasOpen = adc.isStreamOpen();
    stopInput();
    
    if(wasOpen) startInput(callback, data);
}

void AudioInputManager::setInputDevice(int index) {
    std::vector<unsigned int> ids = adc.getDeviceIds();
    if(index > ids.size()) return;
    parameters.deviceId = ids[index];
    restartInput();
}

void AudioInputManager::setBufferFrames(unsigned int n) {
    bufferFrames = n;
    restartInput();
}