#include "checks_own.hpp"

std::map<uint16_t, uint8_t> Checks_Own::get_world_checks(uint8_t world)
{
    // get the string representation of the world
    std::string world_str = worlds_byte_string.at(world);

    std::map<uint16_t, uint8_t> checks;
    if (world_str.empty()) return checks;

    checks.merge(get_chests(world_str));
    checks.merge(get_bonus_levels(world_str));
    checks.merge(get_progress(world_str));
    checks.merge(get_drive_levels());
    checks.emplace(get_level());

    return checks;
}

std::map<uint16_t, uint8_t> Checks_Own::get_chests(std::string world)
{
    std::map<uint16_t, uint8_t> open_chests;
    auto world_chests = chests[world];
    for (auto chest : world_chests)
    {
        uint8_t val = MemoryLib::ReadByte(Anchors::SAVE + chest.first);
        if (val > 0)
        {
            open_chests.emplace(chest.first, val);
        }
    }
    return open_chests;
}

std::map<uint16_t, uint8_t> Checks_Own::get_bonus_levels(std::string world)
{
    std::map<uint16_t, uint8_t> checks_bonus_levels;
    for (auto bl : bonus_levels_sora)
    {
        uint8_t val = MemoryLib::ReadByte(Anchors::SAVE + bl.first);
        if (val > 0)
        {
            auto it = checks_bonus_levels.find(bl.first);
            if (it == checks_bonus_levels.end())
            {
                checks_bonus_levels.emplace(bl.first, val);
            }
        }
    }
    return checks_bonus_levels;
}

std::map<uint16_t, uint8_t> Checks_Own::get_progress(std::string world)
{
    std::map<uint16_t, uint8_t> checks_progress_flags;
    auto world_progress = progress_flags[world];
    for (auto flag : world_progress)
    {
        checks_progress_flags.emplace(flag, MemoryLib::ReadByte(Anchors::SAVE + flag));
    }
    return checks_progress_flags;
}

std::pair<uint16_t, uint8_t> Checks_Own::get_level()
{
    uint8_t lvl = MemoryLib::ReadByte(Anchors::SAVE + cur_level_addr);
    return {0x000F, lvl};
}

std::map<uint16_t, uint8_t> Checks_Own::get_drive_levels()
{
    std::map<uint16_t, uint8_t> d_lvls;
    for (auto form : drive_levels)
    {
        d_lvls.emplace(form.first, MemoryLib::ReadByte(Anchors::SAVE + form.first + 2));
    }
    return d_lvls;
}

