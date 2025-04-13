#include "cartridge.hpp"

Cartridge::~Cartridge() {
    if (rom) {
        delete[] rom;
        DEBUG_INFO("Cartridge memory released.");
    }
    else {
        DEBUG_WARN("Cartridge memory was not allocated.");
    }
}

Cartridge::Cartridge(const u8& rom) : rom(nullptr) {
    for (int i = 0; i < 4; ++i) {
        entrypoint[i] = 0x00;
    }
    for (int i = 0; i < 0x30; ++i) {
        logo[i] = 0x00;
    }
    for (int i = 0; i < 16; ++i) {
        title[i] = 0x00;
    }
    newLicenseeCode = 0x00;
    sgbFlag = 0x00;
    cartridgeType = 0x00;
    romSize = 0x00;
    ramSize = 0x00;
    destinationCode = 0x00;
    oldLicenseeCode = 0x00;
    romVersion = 0x00;
    headerChecksum = 0x00;
    globalChecksum = 0x00;
}

bool Cartridge::LoadROM(const std::string& filename) {
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

    rom = new u8[romSize];
    
    if (!romFile.read(reinterpret_cast<char*>(rom), romSize)) {
        DEBUG_ERROR("Failed to read ROM file: " + filename);
        delete[] rom;
        rom = nullptr;

        return false;
    }
    DEBUG_INFO("Loaded ROM: " + filename + " (" + std::to_string(romSize) + " bytes)");

    return true;
}

void Cartridge::InitCartridge() {
    for (int i = 0; i < 4; ++i) {
        entrypoint[i] = rom[0x100 + i];
    }
    for (int i = 0; i < 0x30; ++i) {
        logo[i] = rom[0x0104 + i];
    }
    for (int i = 0; i < 16; ++i) {
        title[i] = rom[0x0134 + i];
    }
    newLicenseeCode = rom[0x013F];
    sgbFlag = rom[0x0143];
    cartridgeType = rom[0x0147];
    romSize = rom[0x0148];
    ramSize = rom[0x0149];
    destinationCode = rom[0x014A];
    oldLicenseeCode = rom[0x014B];
    romVersion = rom[0x014C];
    headerChecksum = rom[0x014D];
    globalChecksum = (rom[0x014E] << 8) | rom[0x014F];

    DEBUG_INFO("Cartridge initialized.");
}