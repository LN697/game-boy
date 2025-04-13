#include <iostream>

#include "debug.hpp"
#include "emulator.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        DEBUG_ERROR("Usage: " << argv[0] << " <ROM file>");

        return 1;
    }
    
    Emulator emulator(Model::DMG);

    emulator.InitEmulator();
    
    if (!emulator.LoadROM(argv[1])) {
        DEBUG_ERROR("Failed to load ROM file: " << argv[1]);
        
        return 1;
    }

    InitDisplay();

    emulator.LoadCartridge();
    emulator.DumpCartridgeHeader();
    emulator.UnloadCartridge();

    // For DEBUGGING only
    emulator.SetState(State::UNKNOWN);

    while (emulator.GetState() != State::STOPPED) {
        if (emulator.GetState() == State::RUNNING) {
            emulator.StepCPU();
            UpdateDisplay();
        }
        else if (emulator.GetState() == State::PAUSED) {
            continue;
        }
        else if (emulator.GetState() == State::UNKNOWN) {
            DEBUG_ERROR("Unknown state encountered.");
            break;
        }
    }

    // while (emulator.GetState() != State::STOPPED) {
    //     emulator.StepCPU();
    //     UpdateDisplay();
        
    //     if (emulator.GetState() == State::UNKNOWN) {            
    //         DEBUG_ERROR("Unknown state encountered.");
    //         break;
    //     }
    // }

    emulator.StopEmulator();
    DEBUG_INFO("Emulator stopped.");

    return 0;
}