#pragma once

#include "common.hpp"
#include "debug.hpp"

class Cartridge {
    private:
        u8 entrypoint[4];
        u8 logo[0x30];
        char title[16];
        u16 newLicenseeCode;
        u8 sgbFlag;
        u8 cartridgeType;
        u8 romSize;
        u8 ramSize;
        u8 destinationCode;
        u8 oldLicenseeCode;
        u8 romVersion;
        u8 headerChecksum;
        u16 globalChecksum;

        u8* rom;

    public:
        Cartridge(const u8& rom);
        ~Cartridge();
        bool LoadROM(const std::string& filename);
        void InitCartridge();
};