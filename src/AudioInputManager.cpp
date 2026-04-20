#include "AudioInputManager.h"

AudioInputManager::AudioInputManager(NoteDetector* detector) {
    if(detector == nullptr) {
        throw std::invalid_argument("callback function is nullptr");
    }

    nd = detector;
    options.flags = RTAUDIO_MINIMIZE_LATENCY;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
}

//Opens and starts stream
void AudioInputManager::startInput() {
    //adc.openStream(NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &audioCallback, nullptr, &options);
    adc.startStream();
}

//Stops and closes stream
void AudioInputManager::stopInput() {
    adc.stopStream();
    if (adc.isStreamOpen()) {
        adc.closeStream();
    }
}

int AudioInputManager::audioCallback(void *outputBuffer,
                  void *inputBuffer,
                  unsigned int nBufferFrames,
                  double streamTime,
                  RtAudioStreamStatus status,
                  void *userData) 
{
   // nd->getMidiNoteFromBuffer();
}