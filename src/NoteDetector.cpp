#include "NoteDetector.h"

void NoteDetector::init() {
    Yin_init(&yin, frames, pThreshold);
}

void NoteDetector::init(unsigned int bufferLenght, float threshold) {
    frames = bufferLenght;
    pThreshold = threshold;
    Yin_init(&yin, bufferLenght, threshold);
}

//Uses YIN to get pitch
int NoteDetector::getMidiNoteFromBuffer (void *inputBuffer) {
    input = static_cast<int16_t*>(inputBuffer);

    pitch = Yin_getPitch(&yin, input);
    if(pitch <= 0.0f) return -1;

    return (int) round(12 * log2f(pitch / 440.0f) + 69);
}