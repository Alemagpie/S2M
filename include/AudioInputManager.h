#ifndef AUDIO_INPUT_MNG_H
#define AUDIO_INPUT_MNG_H

#include <RtAudio.h>
#include "NoteDetector.h"

class AudioInputManager {
    public:
    AudioInputManager();
    
    int16_t* getInputBuffer() { return input; }
    unsigned int getBufferLenght() { return bufferFrames; }
    void startInput(RtAudioCallback audioCallback, void *userData);
    void stopInput();
 
    private:
    RtAudio adc;
    std::vector<unsigned int> deviceIds;
    RtAudio::StreamParameters parameters;
    RtAudio::StreamOptions options;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 2048;

    int16_t *input = nullptr;
};

#endif