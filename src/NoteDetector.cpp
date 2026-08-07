#include "NoteDetector.h"

void NoteDetector::init(unsigned int bufferLenght, float threshold) {
    Yin_init(&yin, bufferLenght, threshold);
}

//Uses YIN to get pitch
int NoteDetector::getMidiNoteFromBuffer (void *inputBuffer) {
    input = static_cast<int16_t*>(inputBuffer);

    pitch = Yin_getPitch(&yin, input);
    if(pitch <= 0.0f) return -1;

    return (int) round(12 * log2f(pitch / 440.0f) + 69);

    /*// Example: just inspect samples
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        int16_t sample = input[i];  // mono assumption for now
        // Do something with sample
    }*/
}