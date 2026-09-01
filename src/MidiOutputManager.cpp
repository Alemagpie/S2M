#include "MidiOutputManager.h"

//Applies modifier to input note
int MidiOutputManager::modNote(int inputNote) {
    int modifier = 0;

    switch(currentMod) {
        //OCTAVE_DOWN_2
        case 1:
        modifier = -24;
        break;

        //OCTAVE_DOWN_1
        case 2:
        modifier = -12;
        break;

        //FIFTH_DOWN
        case 3:
        modifier = -5;
        break;

        //MINOR_THIRD_UP
        case 4:
        modifier = 3;
        break;

        //MAJOR_THIRD_UP
        case 5:
        modifier = 4;
        break;

        //FOURTH_UP
        case 6:
        modifier = 5;
        break;

        //FIFTH_UP
        case 7:
        modifier = 7;
        break;

        //MINOR_SEVENTH_UP
        case 8:
        modifier = 10;
        break;

        //MAJOR_SEVENTH_UP
        case 9:
        modifier = 11;
        break;

        //OCTAVE_UP_1
        case 10: 
        modifier = 12;
        break;

        //OCTAVE_UP_2 
        case 11:
        modifier = 24;
        break;

        case 0: default:
        modifier = 0;
        break;
    }

    int outputNote = inputNote + modifier;
    if(outputNote < 0) outputNote = 0;
    if(outputNote > 127) outputNote = 127;

    return outputNote;
}

void MidiOutputManager::changeMod(unsigned int mode) {
   // silenceAll();
    currentMod = (Modifier) mode;
}

void MidiOutputManager::noteOn(int newNote) {
    writeMIDIOut(true, modNote(newNote));
}

void MidiOutputManager::noteOff(int lastNote) {
    writeMIDIOut(false, modNote(lastNote));
}

//Writes midi output
void MidiOutputManager::writeMIDIOut(bool status, int note) {
    /**
    * Note on: 144 (d) = 0x90
    * Note off: 128 (d) = 0x80
    */
    if(muted) return;

    if(status) {
        message[0] = 0x90;
        message[2] = noteAttack;
    } else {
        message[0] = 0x80;
        message[2] = noteRelease;
    }

    message[1] = note;

    midiout.sendMessage(&message);
}

void MidiOutputManager::silenceAll() {
    message[0] = 0xFF;  //Reset message
    message[1] = message[2] = 0;
    midiout.sendMessage(&message);
}

//Selects port to output to
void MidiOutputManager::openPort(unsigned int p) {
    midiout.closePort();
    unsigned int count = midiout.getPortCount();
    std::cout << "MIDI ports available: " << count << "\n";
    for(int i = 0; i < count; i++) {
        std::string port = midiout.getPortName(i);
        if(port != "") std::cout << "- Port: " << port << "\n";
    }

    if (count > p) {
        try {
            midiout.openPort(p);
            std::cout << "Opened MIDI port " << p << ": " << midiout.getPortName(p) << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Failed to open MIDI port: " << e.what() << std::endl;
        }
    } else {    
        std::cerr << "No MIDI port at index " << p << " available! \n";
    }
    std::cout << "\n\n";
}