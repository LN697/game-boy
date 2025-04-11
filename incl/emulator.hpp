#pragma once

#include "debug.hpp"
#include "common.hpp"
#include "display.hpp"

enum State {
    STOPPED,
    RUNNING,
    PAUSED
};

enum Model {
    DMG,                                    // Game Boy
    MGB,                                    // Game Boy Pocket
    SGB,                                    // Super Game Boy
    CGB                                     // Game Boy Color
};


class Emulator {
    private:
        State state;
        Model model;

        std::unique_ptr<uint8_t[]> memory;  // Main memory - 32KiB (up to 8MiB for CGB) 16-bit address space

        std::unique_ptr<uint8_t[]> wram;    // Work RAM - 8KiB (32KiB for CGB)
        std::unique_ptr<uint8_t[]> vram;    // Video RAM - 8KiB (16KiB for CGB)
        
        uint64_t ticks;                     // Number of ticks since the emulator started




    public:
        Emulator(Model);
        ~Emulator();

        bool LoadROM(const std::string& filename);
        void InitEmulator();
        void StopEmulator();
        void ResetEmulator();
        void StepCPU();
        State GetState() const;
};
