#ifndef AUDIO_INPUT_MNG_H
#define AUDIO_INPUT_MNG_H

#include <RtAudio.h>
#include "NoteDetector.h"

//Handles audio buffering
class AudioInputManager {
    public:
    RtAudio adc;
    AudioInputManager();
    
    int16_t* getInputBuffer() { return input; }
    unsigned int getBufferLenght() { return bufferFrames; }
    void startInput(RtAudioCallback audioCallback, void *userData);
    void stopInput();
    void restartInput();

    void setInputDevice(int index);
    void setBufferFrames(unsigned int n);
 
    private:
    std::vector<unsigned int> deviceIds;
    RtAudio::StreamParameters parameters;
    RtAudio::StreamOptions options;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 1024;

    RtAudioCallback callback;
    void *data;

    int16_t *input = nullptr;
};

#endif