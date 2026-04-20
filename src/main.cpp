#include <RtAudio.h>
#include <Yin.h>
#include <RtMidi.h>
#include <iostream>
#include "AudioInputManager.h"
#include "NoteDetector.h"
#include "MidiOutputManager.h"

//cmake --build build --config Release
//start build/Release/s2m.exe

int main() {
    try {
        /*AudioInputManager audioMan;
        NoteDetector noteDet;
        MidiOutputManager midiMan;

        audioMan.startInput(&(noteDet.getMidiNoteFromBuffer));*/

    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}