#include "emulator.hpp"

using namespace DEBUG;

Emulator::Emulator(Model model) : state(STOPPED), model(model) {
    memory = nullptr;
    DEBUG_INFO("Emulator initialized.");
}

Emulator::~Emulator() {
    if (memory) {
        DEBUG_INFO("Emulator memory released.");
    }
    else {
        DEBUG_WARN("Emulator memory was not allocated.");
    }
}

bool Emulator::LoadROM(const std::string& filename) {
    std::ifstream romFile(filename, std::ios::binary | std::ios::ate);
    if (!romFile.is_open()) {
        DEBUG_ERROR("Failed to open ROM file: " + filename);
        return false;
    }

    std::streamsize romSize = romFile.tellg();
    romFile.seekg(0, std::ios::beg);

    if (romSize <= 0) {
        DEBUG_ERROR("ROM file is empty or invalid: " + filename);
        return false;
    }

    memory = std::make_unique<uint8_t[]>(romSize);

    if (!romFile.read(reinterpret_cast<char*>(memory.get()), romSize)) {
        DEBUG_ERROR("Failed to read ROM file: " + filename);
        return false;
    }

    DEBUG_INFO("Loaded ROM: " + filename + " (" + std::to_string(romSize) + " bytes)");
    return true;
}

void Emulator::InitEmulator() {
    state = RUNNING;
    ticks = 0;
    
    // Allocate memory for the emulator
    memory = std::make_unique<uint8_t[]>(0xFFFF); // 64KiB of addressable memory
    // Initialize memory model vram, wram, etc.
    
    InitDisplay();

    DEBUG_INFO("Emulator initialized.");
}

void Emulator::StopEmulator() {
    state = STOPPED;
}

void Emulator::ResetEmulator() {
    state = STOPPED;
}

void Emulator::StepCPU() {
    if (state == RUNNING) {
        // Execute one CPU cycle
    }
}

State Emulator::GetState() const {
    switch (state) {
        case STOPPED:
            DEBUG_INFO("Emulator state: STOPPED");
            break;
        case RUNNING:
            DEBUG_INFO("Emulator state: RUNNING");
            break;
        case PAUSED:
            DEBUG_INFO("Emulator state: PAUSED");
            break;
    }

    return state;
}




