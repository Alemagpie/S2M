#ifndef MIDI_OUT_H
#define MIDI_OUT_H

#include <math.h>
#include <RtMidi.h>

class MidiOutputManager {
    public:
    RtMidiOut midiout;
    MidiOutputManager() {
        message.resize(3);
    }
    int modNote(int inputNote);
    void changeMod(unsigned int mode);
    void mute() { muted = true; }
    void unmute() { muted = false; }

    void noteOn(int newNote);
    void noteOff(int lastNote);
    void silenceAll();

    void openPort(unsigned int p);

    private:
    void writeMIDIOut(bool status, int note);

    enum Modifier {
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
    Modifier currentMod = NONE;

    unsigned int noteAttack = 1;
    unsigned int noteRelease = 1;

    bool muted = false;
    std::vector<unsigned char> message;
};

#endif