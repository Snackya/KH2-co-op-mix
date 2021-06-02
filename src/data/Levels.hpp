#pragma once
#include <cstdint>
#include "Anchors.hpp"
namespace Levels
{
    // BTL0 anchor
    static inline uint32_t levels_start = 0x25928;

    // SAVE anchor
    static inline uint32_t cur_level_addr = 0x24F0 + 0xF;   //stat addr + lvl offset of 0xF

    static inline uint8_t weapon_offset = 0;

    static void set_weapon_offset()
    {
        uint8_t dream_wep = MemoryLib::ReadByte(SAVE + 0x24F0 + 0xE);
        switch (dream_wep)
        {
        case 0: weapon_offset = 0x08;
            break;
        case 1: weapon_offset = 0x0A;
            break;
        case 2: weapon_offset = 0x0C;
            break;
        default: weapon_offset = 0x08;
        }
    };
}