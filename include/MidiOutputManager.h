#ifndef MIDI_OUT_H
#define MIDI_OUT_H

#include <math.h>
#include <RtMidi.h>

class MidiOutputManager {
    public:
    void modNote();
    int writeMIDIOut(bool status);

    void openPort(unsigned int p);

    private:
    enum modifier {
        NONE,
        OCTAVE_DOWN_2,
        OCTAVE_DOWN_1,
        FIFTH_DOWN,
        MINOR_THIRD_UP,
        MAJOR_THIRD_UP,
        FOURTH_UP,
        FIFTH_UP,
        MINOR_SEVENTH_UP,
        MAJOR_SEVENTH_UP,
        OCTAVE_UP_1,
        OCTAVE_UP_2     
    };

    modifier currentMod;
    int inputNote;
    int currentNote;
    bool noteOn = false;
    unsigned int noteAttack = 90;
    unsigned int noteRelease = 40;

    RtMidiOut midiout;
    std::vector<unsigned char> message;
};

#endif