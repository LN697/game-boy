#include "emulator.hpp"

Emulator::Emulator(Model model) : state(STOPPED), model(model) {
    memory = nullptr;
    DEBUG_INFO("Emulator initialized.");
}

Emulator::~Emulator() {
    if (memory) {
        delete[] memory;
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
        state = UNKNOWN;
        DEBUG_INFO("Emulator state changed to: UNKNOWN")

        return false;
    }

    std::streamsize romSize = romFile.tellg();
    romFile.seekg(0, std::ios::beg);

    if (romSize <= 0) {
        DEBUG_ERROR("ROM file is empty or invalid: " + filename);
        state = UNKNOWN;
        DEBUG_INFO("Emulator state changed to: UNKNOWN")

        return false;
    }

    memory = new u8[romSize];

    if (!romFile.read(reinterpret_cast<char*>(memory), romSize)) {
        DEBUG_ERROR("Failed to read ROM file: " + filename);
        state = UNKNOWN;
        DEBUG_INFO("Emulator state changed to: UNKNOWN")

        return false;
    }
    DEBUG_INFO("Loaded ROM: " + filename + " (" + std::to_string(romSize) + " bytes)");

    return true;
}

void Emulator::InitEmulator() {
    state = RUNNING;
    ticks = 0;

    DEBUG_INFO("Emulator initialized.");
}

void Emulator::StopEmulator() {
    state = STOPPED;
}

void Emulator::ResetEmulator() {
    state = STOPPED;
}

void Emulator::StepCPU() {
    if (state == RUNNING) { // state check redundant as per current implementation
        // Execute one CPU cycle
        ticks++;
        // Update memory, registers, etc.
        // For now, just a placeholder
    }
}

// Getter functions

u8 Emulator::ReadByte(u16 address) const {
    return memory[address];
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



// Setter functions

void Emulator::WriteByte(u16 address, u8 value) {
    if (address < 0xFFFF) {
        memory[address] = value;
    }
    else {
        DEBUG_ERROR("Attempted to write to invalid memory address: " + std::to_string(address));
        state = UNKNOWN;
        DEBUG_INFO("Emulator state changed to: UNKNOWN");
    }
}

void Emulator::SetState(State newState) {
    state = newState;
    DEBUG_INFO("Emulator state changed to: " + std::to_string(state));
}

