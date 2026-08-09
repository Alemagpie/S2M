#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#include "InstanceManager.h"

//Sits besides InstanceManager
class UIManager {
    public:
    UIManager(InstanceManager *man);
    void draw();

    private:
    InstanceManager *instanceManager;

    void refreshInputDevices();
    void refreshMidiPorts();

    //UI states
    std::vector<std::string> inputDeviceNames;
    std::vector<const char*> inputDeviceNamePtrs;
    int inputDeviceSelector = 0;
    int bufferFramesSelector = 2;
    float yinProbabilityThreshold = 0.1f;
    float rmsDetectionThreshold = 0.1f;
    int noteModifier = 0;
    std::vector<std::string> midiPortNames;  
    std::vector<const char*> midiPortNamesPtrs;
    int midiPortSelector = 0;
    bool muted = false;
    bool running = false;
};

#endif