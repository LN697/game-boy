#include "cartridge.hpp"

Cartridge::Cartridge() {
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

    DEBUG_INFO("Cartridge initialized: default constructor.");
}

Cartridge::Cartridge(const u8* romData, size_t size) {
    rom = new u8[size];
    if (rom) {
        std::copy(romData, romData + size, rom);
        DEBUG_INFO("Cartridge memory allocated and initialized.");
    }
    else {
        DEBUG_ERROR("Failed to allocate memory for cartridge.");
    }
}

Cartridge::~Cartridge() {
    if (rom) {
        delete[] rom;
        DEBUG_INFO("Cartridge memory released.");
    }
    else {
        DEBUG_WARN("Cartridge memory was not allocated.");
    }
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

void Cartridge::DumpHeader() const {
    DEBUG_INFO("Cartridge Header:");
    DEBUG_INFO("Entry Point: " + std::to_string(entrypoint[0]) + " " + std::to_string(entrypoint[1]) + " " + std::to_string(entrypoint[2]) + " " + std::to_string(entrypoint[3]));
    DEBUG_INFO("Logo: " + std::to_string(logo[0]) + " " + std::to_string(logo[1]) + " ...");
    DEBUG_INFO("Title: " + std::string(title, 16));
    DEBUG_INFO("New Licensee Code: " + std::to_string(newLicenseeCode));
    DEBUG_INFO("SGB Flag: " + std::to_string(sgbFlag));
    DEBUG_INFO("Cartridge Type: " + std::to_string(cartridgeType));
    DEBUG_INFO("ROM Size: " + std::to_string(romSize));
    DEBUG_INFO("RAM Size: " + std::to_string(ramSize));
    DEBUG_INFO("Destination Code: " + std::to_string(destinationCode));
    DEBUG_INFO("Old Licensee Code: " + std::to_string(oldLicenseeCode));
    DEBUG_INFO("ROM Version: " + std::to_string(romVersion));
    DEBUG_INFO("Header Checksum: " + std::to_string(headerChecksum));
    DEBUG_INFO("Global Checksum: " + std::to_string(globalChecksum));
}