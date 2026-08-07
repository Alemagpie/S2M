#include "InstanceManager.h"
#include <iostream>

//cmake -S . -B build
//cmake --build build --config Release
//start build/Release/s2m.exe

int main() {
    try {
        InstanceManager mgr;
        mgr.start();
        std::cin.get();  // keep alive until Enter
        mgr.stop();
    } catch (const std::exception &e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        std::cin.get();
    }

    return 0;
}