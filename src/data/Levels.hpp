#pragma once
#include <cstdint>
#include "Anchors.hpp"

// BTL0 anchor
static const uint32_t levels_start = 0x25928;

// SAVE anchor
static const uint32_t cur_level_addr = 0x24F0 + 0xF;   //stat addr + lvl offset of 0xF

static uint8_t get_weapon_offset()
{
    uint8_t dream_wep = MemoryLib::ReadByte(Anchors::SAVE + 0x24F0 + 0xE);
    switch (dream_wep)
    {
    case 0: 
        return 0x08;
    case 1: 
        return 0x0A;
    case 2:
        return 0x0C;
    }
};