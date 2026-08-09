#include "UIManager.h"

static const char* bufferSizes[] = {
    "256",
    "512",
    "1024",
    "2048"
};

static const char* modifierNames[] = {
    "None",
    "Octave Down 2",
    "Octave Down 1",
    "Fifth Down",
    "Minor 3rd Up",
    "Major 3rd Up",
    "Fourth Up",
    "Fifth Up",
    "Minor 7th Up",
    "Major 7th Up",
    "Octave Up 1",
    "Octave Up 2"
};

UIManager::UIManager(InstanceManager *man) {
    instanceManager = man;
    refreshInputDevices();
    refreshMidiPorts();
}

void UIManager::draw() {
    ImGui::Begin("Signal To MIDI");

    //input device
    if (ImGui::Combo("Input device", &inputDeviceSelector, inputDeviceNamePtrs.data(), (int)inputDeviceNamePtrs.size())) {
        instanceManager->setInputDevice(inputDeviceSelector);
    }

    //buffer frames
    if (ImGui::Combo("Buffer size", &bufferFramesSelector, bufferSizes, IM_ARRAYSIZE(bufferSizes))) {
        instanceManager->setBufferFrames(atoi(bufferSizes[bufferFramesSelector]));
    }

    if (ImGui::SliderFloat("Confidence Threshold", &yinProbabilityThreshold, 0.0f, 1.0f)) {
        instanceManager->setYinThreshold(yinProbabilityThreshold);
    }

    if (ImGui::SliderFloat("RMS detection Threshold", &rmsDetectionThreshold, 0.0f, 1.0f)) {
        instanceManager->setRMSThreshold(rmsDetectionThreshold);
    }
    
    if (ImGui::Combo("Note modifier", &noteModifier, modifierNames, IM_ARRAYSIZE(modifierNames))) {
        instanceManager->setNoteModifier(noteModifier);
    }

    //midi port
    if (ImGui::Combo("MIDI output", &midiPortSelector, midiPortNamesPtrs.data(), (int)midiPortNamesPtrs.size())) {
        instanceManager->setMidiPort(midiPortSelector);
    }

    //Muted
    if(ImGui::Checkbox("Mute", &muted)) {
        instanceManager -> mute_unmute(muted);
    }

    if (ImGui::Button(running ? "Stop" : "Start")) {
        running = !running;
        running ? instanceManager->start() : instanceManager->stop();
    }

    //ImGui::Text("Detected note: %d", instanceManager->lastDetectedNote.load());
    //ImGui::Text("Confidence: %.2f", instanceManager->lastConfidenceValue.load());

    ImGui::End();
}

void UIManager::refreshInputDevices() {
    inputDeviceNames = instanceManager->getAvailableInputDevices();
    inputDeviceNamePtrs.clear();

    for(auto& name : inputDeviceNames) {
        inputDeviceNamePtrs.push_back(name.c_str());
    }
}

void UIManager::refreshMidiPorts() {
    midiPortNames = instanceManager->getAvailableOutputPorts();
    midiPortNamesPtrs.clear();

    for(auto& name : midiPortNames) {
        midiPortNamesPtrs.push_back(name.c_str());
    }
}