#ifndef INSTANCE_MANAGER_H
#define INSTANCE_MANAGER_H

#include "AudioInputManager.h"
#include "NoteDetector.h"
#include "MidiOutputManager.h"

//Ties all signal componenets together
class InstanceManager {
    public:
    void start();
    void stop();

    void setInputDevice(int index);
    std::vector<std::string> getAvailableInputDevices();
    void setBufferFrames(unsigned int n);
    void setYinThreshold(float t);
    void setRMSThreshold(float t);
    void setNoteModifier(unsigned int i);
    void setMidiPort(int index);
    std::vector<std::string> getAvailableOutputPorts();
    void mute_unmute(bool s);

    private:
    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

    int onAudioBlock(int16_t *inputBuffer, unsigned nFrames, RtAudioStreamStatus status);

    AudioInputManager audioIn;
    NoteDetector noteDet;
    MidiOutputManager midiOut;

    //C1 = 0
    std::string getNoteFromMidi(unsigned int midi) {
        std::vector<std::string> notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "B#"};
        int octave = (midi / 12) + 1;
        int offset = midi % 12;

        return notes[offset] + std::to_string(octave) + "\n";
    }

    int lastNote = -1;
    bool noteActive = false;

    //Parameters
    unsigned int inputDeviceID;
    unsigned int bufferFrames;
    float yinProbabilityThreshold;
    float rmsDetectionThreshold;
    unsigned int noteModifier;
    unsigned int midiPort;

    /*
    Variables that can be changed:
    - Input device
    - Buffer frames
    - Detection threshold
    - Note modifier
    - Midi port
    - RMS threshold
    - Muted
    */
};

#endif