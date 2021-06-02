#include "checks_other.hpp"

//TODO: rewrite open_chests() to work for chests and flags
// open all chests of partner players, so items cannot be received twice
// overwrites bitmask values to open a range of chests
std::map<uint16_t, uint8_t> Checks_Other::open_chests(std::map<uint16_t, uint8_t>& other_vals)
{
    auto itr = other_vals.lower_bound(0x2300);
    auto upper_limit = other_vals.upper_bound(0x23FF);
    std::map<uint16_t, uint8_t> m_chests_added;
    // loop over all "chest is open" address,status pairs
    for (; itr != upper_limit; itr++)
    {
        uint8_t before = MemoryLib::ReadByte(SAVE + itr->first);
        uint8_t after = before | itr->second;
        uint8_t added = after - before;
        // perform a bit-wise OR at every address for own and partner value
        // bit-wise OR ensures the 2 values per address get proerply "merged"
        MemoryLib::WriteByte(SAVE + itr->first, after);

        m_chests_added.emplace(itr->first, added);
    }

    return m_chests_added;
}

// actually find out *which* chests have been opened. the result is new_item_addr
std::vector<uint16_t> Checks_Other::from_chests(std::map<uint16_t, uint8_t> chests_added)
{
    std::vector<uint16_t> id_list;

    // iterate over all areas and their chests
    for (auto area : chests)
    {
        // iterate over all newly added partner chests
        for (auto added : chests_added)
        {
            // get all (address, value) pairs for the current bitmask address
            auto it = area.second.equal_range(added.first);
            for (auto itr = it.first; itr != it.second; ++itr)
            {
                // split the value (byte) of the added chests into its bits to check against the bitmask lu-table
                vector<uint8_t> new_vals = Utils::mask_to_values(added.second);

                // split-byte-value matches one of the bitmasks. this chest has been opened.
                auto val_it = std::find(new_vals.begin(), new_vals.end(), itr->second.first);
                if (val_it != new_vals.end())
                {
                    auto id = MemoryLib::ReadShort(SYS3 + itr->second.second);
                    id_list.push_back(id);
                }
            }
        }
    }

    return id_list;
}

std::vector<uint16_t> Checks_Other::from_drives(std::map<uint16_t, uint8_t>& other_vals)
{
    auto ov_itr = other_vals.lower_bound(0x32F4);
    auto upper_limit = other_vals.upper_bound(0x33D4);
    std::vector<uint16_t> id_list;

    for (; ov_itr != upper_limit; ++ov_itr)
    {
        uint16_t addr = ov_itr->first;
        uint8_t level = ov_itr->second;
        uint8_t before = MemoryLib::ReadByte(SAVE + addr + 2);
        // drive level higher than partner's. nothing to do
        if (before >= level) continue;

        // increase drive form level
        if (SHARE_DRIVES)
        {
            MemoryLib::WriteByte(SAVE + ov_itr->first + 2, ov_itr->second);
        }

        // workaround to make granting drive levels optional
        // new drive level is bigger than what is stored
        if (level > workaround_drivelvl_storage[addr])
        {
            workaround_drivelvl_storage[addr] = level;

            // go through all new higher level checks
            std::string form_name = drive_levels[addr];
            for (uint8_t i = before + 1; i <= level; ++i)
            {
                auto check_addr = drive_checks[form_name][i];
                auto id = MemoryLib::ReadShort(BTL0 + check_addr);
                id_list.push_back(id);
            }
        }
    }
    return id_list;
}

std::vector<uint16_t> Checks_Other::from_bonus_levels(std::map<uint16_t, uint8_t>& other_vals)
{
    auto ov_itr = other_vals.lower_bound(0x3700);
    auto upper_limit = other_vals.upper_bound(0x37FF);
    std::vector<uint16_t> id_list;

    for (; ov_itr != upper_limit; ++ov_itr)
    {
        // merge new checks with existing ones
        uint8_t before = MemoryLib::ReadByte(SAVE + ov_itr->first);
        uint8_t after = before | ov_itr->second;
        uint8_t added = after - before;
        MemoryLib::WriteByte(SAVE + ov_itr->first, after);

        vector<uint8_t> split_vals = Utils::mask_to_values(added);

        auto bls_range = bonus_levels_sora.equal_range(ov_itr->first);
        for (auto bls_itr = bls_range.first; bls_itr != bls_range.second; ++bls_itr)
        {
            // split-byte-value matches one of the bitmasks. grant the corresponding items/abilities/etc.
            auto val_it = std::find(split_vals.begin(), split_vals.end(), bls_itr->second.first);
            if (val_it != split_vals.end())
            {
                auto addr = bls_itr->second.second[2];
                uint16_t item1 = MemoryLib::ReadShort(SAVE + addr);
                uint16_t item2 = MemoryLib::ReadShort(SAVE + addr + 2);
                if (item1 != 0)  id_list.push_back(item1);
                if (item2 != 0)  id_list.push_back(item2);
            }
        }
    }
    return id_list;
}

std::vector<uint16_t> Checks_Other::from_levels(std::map<uint16_t, uint8_t>& other_vals)
{
    std::vector<uint16_t> id_list;

    uint8_t other_level = other_vals[0x000F];   // dummy key for level value
    uint8_t cur_level = MemoryLib::ReadByte(SAVE + cur_level_addr);

    if (cur_level >= other_level) return id_list;
    if (highest_level_granted >= other_level) return id_list;

    uint8_t start = (std::max)(cur_level, highest_level_granted);

    for (uint8_t i = start + 1; i <= other_level; ++i)
    {
        uint32_t addr = MemoryLib::ReadShort(
            BTL0 + levels_start + i + weapon_offset
        );
        uint16_t id = MemoryLib::ReadShort(addr);
        id_list.push_back(id);
    }

    if (SHARE_LEVELS)
    {
        MemoryLib::WriteByte(SAVE + cur_level_addr, other_level);
    }

    return id_list;
}

std::vector<uint16_t> Checks_Other::from_popups(std::map<uint16_t, uint8_t>& progress_added)
{
    std::vector<uint16_t> id_list;

    // iterate over all areas
    for (auto area : popups)
    {
        // iterate over all new progress pairs
        for (auto added : progress_added)
        {
            // get all (address, value) pairs for the current bitmask address
            auto it = area.second.equal_range(added.first);
            for (auto itr = it.first; itr != it.second; ++itr)
            {
                // split the value (byte) of the added chests into its bits to check against the bitmask lu-table
                vector<uint8_t> new_vals = Utils::mask_to_values(added.second);

                // split-byte-value matches one of the bitmasks. this chest has been opened.
                auto val_it = std::find(new_vals.begin(), new_vals.end(), itr->second.first);
                if (val_it != new_vals.end())
                {
                    auto id = MemoryLib::ReadShort(SYS3 + itr->second.second);
                    id_list.push_back(id);
                }
            }
        }
    }
    return id_list;
}

std::map<uint16_t, uint8_t> Checks_Other::grant_progress(std::map<uint16_t, uint8_t>& other_vals)
{
    auto itr = other_vals.lower_bound(0x1C00);
    auto upper_limit = other_vals.upper_bound(0x1EFF);
    map<uint16_t, uint8_t> progress_added;
    if (SHARE_PROGRESS)
    {
        for (; itr != upper_limit; itr++)
        {
            uint8_t before = MemoryLib::ReadByte(SAVE + itr->first);
            uint8_t after = before | itr->second;
            uint8_t added = after - before;

            MemoryLib::WriteByte(SAVE + itr->first, after);

            if (added != 0) {
                progress_added.emplace(itr->first, added);
            }
        }
    }
    else
    {
        for (; itr != upper_limit; itr++)
        {
            uint8_t before = 0;
            if (workaround_progress_storage[itr->first])
            {
                before = workaround_progress_storage[itr->first];
            }
            else
            {
                before = MemoryLib::ReadByte(SAVE + itr->first);
            }
            uint8_t after = before | itr->second;
            uint8_t added = after - before;

            if (added != 0) {
                progress_added.emplace(itr->first, added);
                workaround_progress_storage[itr->first] = after;
            }
        }
    }

    return progress_added;
}

std::vector<uint16_t> Checks_Other::find_all_ids(std::map<uint16_t, uint8_t>& other_vals)
{
    std::vector<uint16_t> ids = {};

    // chests
    auto _chests = open_chests(other_vals);
    auto chest_checks = from_chests(_chests);
    ids.insert(ids.end(), chest_checks.begin(), chest_checks.end());

    // levels
    auto _levels = from_levels(other_vals);
    ids.insert(ids.end(), _levels.begin(), _levels.end());

    // drive forms
    auto _drives = from_drives(other_vals);
    ids.insert(ids.end(), _drives.begin(), _drives.end());

    // bonus levels
    auto _bonus = from_bonus_levels(other_vals);
    ids.insert(ids.end(), _bonus.begin(), _bonus.end());

    // popups (e.g. from cutscenes)
    auto _progress = grant_progress(other_vals);
    auto _popups = from_popups(_progress);
    ids.insert(ids.end(), _popups.begin(), _popups.end());

    return ids;
}