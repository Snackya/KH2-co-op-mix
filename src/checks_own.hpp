#pragma once
#include <map>
#include <string>
#include "memory/MemoryLib.hpp"
#include "data/Drives.hpp"
#include "data/Chests.hpp"
#include "data/Levels.hpp"
#include "data/Progress_flags.hpp"
#include "data/Popups.hpp"
#include "data/Bonus_Levels.hpp"

class Checks_Own
{
private:
    static inline std::map<uint8_t, std::string> worlds_byte_string =
    {
        {0x01, "World of Darkness"},
        {0x02, "TT"},
        {0x03, "Destiny Island"},
        {0x04, "HB"},
        {0x05, "BC"},
        {0x06, "OC"},
        {0x07, "AG"},
        {0x08, "LOD"},
        {0x09, "100AW"},
        {0x0A, "PL"},
        {0x0B, "AT"},
        {0x0C, "DC"},
        {0x0D, "DC"},   //in reality, it's TR. but that's just inside DC so whatever
        {0x0E, "HT"},
        {0x0F, "World Map"},
        {0x10, "PR"},
        {0x11, "SP"},
        {0x12, "TWTNW"}
    };

    static std::map<uint16_t, uint8_t> get_chests(std::string world);
    static std::map<uint16_t, uint8_t> get_progress(std::string world);
    static std::pair<uint16_t, uint8_t> get_level();
    static std::map<uint16_t, uint8_t> get_drive_levels();
    static std::map<uint16_t, uint8_t> get_bonus_levels(std::string world);

public:
    static std::map<uint16_t, uint8_t> get_world_checks(uint8_t world);
};