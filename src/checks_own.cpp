#include "checks_own.hpp"

std::map<uint16_t, uint8_t> Checks_Own::get_world_checks(uint8_t world)
{
    // get the string representation of the world
    std::string prev_world_str = worlds_byte_string.at(world);
    std::map<uint16_t, uint8_t> checks;
    if (prev_world_str.empty()) return checks;

    // add all chests that have been opened
    std::map<uint16_t, uint8_t> checks_chests;
    auto world_chests = chests[prev_world_str];
    for (auto chest : world_chests)
    {
        uint8_t val = MemoryLib::ReadByte(SAVE + chest.first);
        if (val > 0)
        {
            checks_chests.emplace(chest.first, val);
        }
    }
    checks.merge(checks_chests);

    // add all bonus levels we currently have
    std::map<uint16_t, uint8_t> checks_bonuses;
    for (auto bl : bonus_levels_sora)
    {
        uint8_t val = MemoryLib::ReadByte(SAVE + bl.first);
        if (val > 0)
        {
            auto it = checks_bonuses.find(bl.first);
            if (it == checks_bonuses.end())
            {
                checks_bonuses.emplace(bl.first, val);
            }
            else
            {
                it->second = it->second | bl.second.first;
            }
        }
    }
    checks.merge(checks_bonuses);

    // these should be a subset of progress flags. idk why this is here rn.
    // TODO: fix
    // add the world's popup checks
    //std::map<uint16_t, uint8_t> checks_popups;
    //auto world_popups = popups[prev_world_str];
    //for (auto pu : world_popups)
    //{
    //    uint8_t val = MemoryLib::ReadByte(SAVE + pu.first);
    //    if (val > 0)
    //    {
    //        checks_chests.emplace(pu.first, val);
    //    }
    //}
    //checks.merge(checks_popups);

    // add the progress flags for this world
    std::map<uint16_t, uint8_t> checks_progress_flags;
    auto world_progress = progress_flags[prev_world_str];
    for (auto flag : world_progress)
    {
        checks_progress_flags.emplace(flag, MemoryLib::ReadByte(SAVE + flag));
    }
    checks.merge(checks_progress_flags);

    // add drive form levels
    std::map<uint16_t, uint8_t> d_lvls;
    for (auto form : drive_levels)
    {
        d_lvls.emplace(form.first, MemoryLib::ReadByte(SAVE + form.first + 2));
    }
    checks.merge(d_lvls);

    // add current Sora level
    uint8_t lvl = MemoryLib::ReadByte(SAVE + cur_level_addr);
    checks.emplace(0x000F, lvl);

    return checks;
}

