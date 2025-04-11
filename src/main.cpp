#include <iostream>

#include "debug.hpp"
#include "emulator.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        DEBUG_ERROR("Usage: " << argv[0] << " <ROM file>");
        return 1;
    }
    
    Emulator emulator(DMG);

    emulator.InitEmulator();
    
    if (!emulator.LoadROM(argv[1])) {
        DEBUG_ERROR("Failed to load ROM file: " << argv[1]);
        return 1;
    }

    while (emulator.GetState() == State::RUNNING) {
        emulator.StepCPU();
        UpdateDisplay();
    }

    emulator.StopEmulator();
    DEBUG_INFO("Emulator stopped.");

    return 0;
}