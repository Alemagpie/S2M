#ifndef INSTANCE_MANAGER_H
#define INSTANCE_MANAGER_H

#include "AudioInputManager.h"
#include "NoteDetector.h"
#include "MidiOutputManager.h"

class InstanceManager {
    public:
    void start();
    void stop();

    private:
    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

    int onAudioBlock(int16_t *inputBuffer, unsigned nFrames, RtAudioStreamStatus status);

    AudioInputManager audioIn;
    NoteDetector noteDet;
    MidiOutputManager midiOut;

    int lastNote = -1;
    bool noteActive = false;
};

#endif