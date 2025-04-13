#pragma once

#include "debug.hpp"
#include "common.hpp"
#include "display.hpp"
#include "cartridge.hpp"

enum State {
    STOPPED,
    RUNNING,
    PAUSED,
    UNKNOWN
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
        Model model;                    // Emulator model

        u8* memory;                     // Main memory - 32KiB (up to 8MiB for CGB) 16-bit address space

        u8* wram;                       // Work RAM - 8KiB (32KiB for CGB)
        u8* vram;                       // Video RAM - 8KiB (16KiB for CGB)
        
        u64 ticks;                      // Number of ticks since the emulator started

        Cartridge* cartridge;           // Pointer to the cartridge object


    public:
        Emulator(Model model);
        ~Emulator();

        bool LoadROM(const std::string& filename);
        void InitEmulator();
        void StopEmulator();
        void ResetEmulator();
        void StepCPU();

        void WriteByte(u16 address, u8 value);
        u8 ReadByte(u16 address) const;
        State GetState() const;
        void SetState(State newState);

        void LoadCartridge();
        void UnloadCartridge();
        void DumpCartridgeHeader() const;
};


// TODO: Implement memory management and cartridge loading and initialization