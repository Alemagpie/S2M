#include "InstanceManager.h"

void InstanceManager::start() {
    noteDet.init(audioIn.getBufferLenght(), 0.1f);
    midiOut.openPort(0);
    audioIn.startInput((RtAudioCallback) audioCallback, this);
}

void InstanceManager::stop() {
    audioIn.stopInput();
    midiOut.silenceAll();
}

int InstanceManager::audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    auto *self = static_cast<InstanceManager*>(userData);
    return self->onAudioBlock(static_cast<int16_t*>(inputBuffer), nBufferFrames, status);
}

int InstanceManager::onAudioBlock(int16_t *inputBuffer, unsigned nFrames, RtAudioStreamStatus status) {
    try {
        float confidence = noteDet.getConfidence();
        int note = noteDet.getMidiNoteFromBuffer(inputBuffer);

        bool validPitch = confidence >= 0.85f && note >= 0 && note <= 127;

        if(!validPitch) {
            if(noteActive){
                midiOut.noteOff(lastNote);
                noteActive = false;
            }

            return 0;
        }

        if(note != lastNote) {
            if(noteActive) midiOut.noteOff(lastNote);
            midiOut.noteOn(note);
            lastNote = note;
            noteActive = true;
        }
    } catch (const std::exception &e) {
        fprintf(stderr, "onAudioBlock exception: %s\n", e.what());
        fflush(stderr);
    } catch (...) {
        fprintf(stderr, "onAudioBlock: unknown exception\n");
        fflush(stderr);
    }

    return 0;
}