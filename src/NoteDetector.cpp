#include "NoteDetector.h"

void NoteDetector::init(unsigned int bufferLenght, float thresold) {
    Yin_init(&yin, bufferLenght, thresold);
}

//Uses YIN to get pitch
int NoteDetector::getMidiNoteFromBuffer (void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    if (status)
    std::cout << "Stream overflow/underflow detected\n";

    input = static_cast<int16_t*>(inputBuffer);

    pitch = Yin_getPitch(&yin, input);

    return (int) round(12 * log2f(pitch / 440.0f) + 69);

    /*// Example: just inspect samples
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        int16_t sample = input[i];  // mono assumption for now
        // Do something with sample
    }*/
}