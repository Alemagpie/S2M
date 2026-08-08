#include "InstanceManager.h"

void InstanceManager::start() {
    
    audioIn.startInput((RtAudioCallback) audioCallback, this);
    noteDet.init(audioIn.getBufferLenght(), 0.1f);
    midiOut.openPort(0);
}

void InstanceManager::stop() {
    audioIn.stopInput();
    midiOut.silenceAll();
}

int InstanceManager::audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    auto *self = static_cast<InstanceManager*>(userData);
    return self->onAudioBlock(static_cast<int16_t*>(inputBuffer), nBufferFrames, status);
    //std::cout << "audio callback" << std::endl;
}

int InstanceManager::onAudioBlock(int16_t *inputBuffer, unsigned nFrames, RtAudioStreamStatus status) {
    try {
        int16_t maxSample = 0;
        
        //RMS indicates the power of the signal
        float rms = 0;
        for(int i = 0; i < audioIn.getBufferLenght(); i++) {
            float s = inputBuffer[i] / 32768.0f;
            rms += s*s;
        }
        rms = std::sqrt(rms/nFrames);
        //If signal has low power, ignore it because it could be a harmonic or just noise
        if(rms < 0.1f) return 0;
        
        float confidence = noteDet.getConfidence();
        int note = noteDet.getMidiNoteFromBuffer(inputBuffer);
        //std::cout << note << "\n";

        bool validPitch = confidence >= 0.95f && note >= 0 && note <= 127;

        if(!validPitch) {
            if(noteActive){
                midiOut.noteOff(lastNote);
                noteActive = false;
            }

            return 0;
        }

        note = midiOut.modNote(note);

        if(note != lastNote) {
            if(noteActive) midiOut.noteOff(lastNote);
            midiOut.noteOn(note);
            //note = midiOut.modNote(note);
            std::cout << getNoteFromMidi(note);
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