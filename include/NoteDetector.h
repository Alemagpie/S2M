#ifndef NOTE_DET_H
#define NOTE_DET_H

#include <Yin.h>
#include <RtAudio.h>
#include <math.h>

class NoteDetector {
    public:
    void init(unsigned int bufferLenght, float thresold);
    int getMidiNoteFromBuffer (void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

    private:
    Yin yin;
    float pitch = 0;
    int16_t* input;
};

#endif