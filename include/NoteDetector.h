#ifndef NOTE_DET_H
#define NOTE_DET_H

extern "C" {
    #include <Yin.h>
}

#include <math.h>

class NoteDetector {
    public:
    void init(unsigned int bufferLenght, float threshold);
    int getMidiNoteFromBuffer (void *inputBuffer);
    float getConfidence() { 
        return yin.probability; 
    }

    private:
    Yin yin;
    float pitch = 0;
    int16_t *input;
    int *outputPtr;
};

#endif