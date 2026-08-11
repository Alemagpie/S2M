#ifndef NOTE_DET_H
#define NOTE_DET_H

extern "C" {
    #include <Yin.h>
}

#include <iostream>
#include <math.h>

class NoteDetector {
    public:
    void init();
    void init(unsigned int bufferLenght, float threshold);
    int getMidiNoteFromBuffer (void *inputBuffer);
    float getConfidence() { 
        return yin.probability; 
    }

    void setFrameNumber(unsigned int n) {
        frames = n;
        init();
    }

    void setThreshold(float t) {
        pThreshold = t;
        init();
    }

    private:
    Yin yin;
    float pitch = 0;
    int16_t *input;
    int *outputPtr;
    unsigned int frames = 1024;
    float pThreshold = 0.1f;
};

#endif