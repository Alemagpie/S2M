
#include "AppWindow.h"
#include "UIManager.h"
#include "InstanceManager.h"
#include <iostream>

//Remove-Item -Recurse -Force build
//cmake -S . -B build
//cmake --build build --config Release
//start build/Release/s2m.exe

int main() {
    try {
        AppWindow window;
        if(!window.init(L"Signal To Midi", 800, 600)) return 1;

        InstanceManager i_mgr;
        UIManager ui_mgr(&i_mgr);

        //It's started by UI
        //i_mgr.start();

        while(window.processMessages()) {
            window.beginFrame();
            ui_mgr.draw();
            window.endFrame();
        }

        //std::cin.get();  // keep alive until Enter
        //i_mgr.stop();
    } catch (const std::exception &e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        std::cin.get();
    }

    return 0;
}