#pragma once

#include "debug.hpp"
#include "common.hpp"

enum State {
    STOPPED,
    RUNNING,
    PAUSED
};

class Emulator {
    private:
        State state;

        std::unique_ptr<uint8_t[]> memory;
        
    public:
        Emulator();
        ~Emulator();

        bool LoadROM(const std::string& filename);
        void InitEmulator();
        void StopEmulator();
        void ResetEmulator();
        void StepCPU();
};
