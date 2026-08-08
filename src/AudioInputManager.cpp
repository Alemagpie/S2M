#include "AudioInputManager.h"

AudioInputManager::AudioInputManager() {
    options.flags = RTAUDIO_MINIMIZE_LATENCY;
    parameters.deviceId = 132; //iRig2 Mic        
    //parameters.deviceId = adc.getDefaultInputDevice();  //This needs to change to be able to select the input
    std::cout << "Using API: " << RtAudio::getApiDisplayName(adc.getCurrentApi()) << "\n";
    unsigned int count = adc.getDeviceCount();
    std::cout << "Found " << count << " devices. \n";
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