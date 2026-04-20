#ifndef AUDIO_INPUT_MNG_H
#define AUDIO_INPUT_MNG_H

#include <RtAudio.h>
#include "NoteDetector.h"

class AudioInputManager {
    public:
    AudioInputManager(NoteDetector* detector);
    int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData); 

    int16_t* getInputBuffer() { return input; }
    unsigned int getBufferLenght() { return bufferFrames; }
    void startInput();
    void stopInput();

    private:
    RtAudio adc;
    std::vector<unsigned int> deviceIds;
    RtAudio::StreamParameters parameters;
    RtAudio::StreamOptions options;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256;

    int16_t *input = nullptr;

    NoteDetector* nd;
};

#endif