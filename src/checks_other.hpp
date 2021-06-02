#pragma once
#include <map>
#include <iostream>
#include <algorithm>
#include "memory/MemoryLib.hpp"
#include "data/Popups.hpp"
#include "data/Chests.hpp"
#include "data/Abilities.hpp"
#include "data/Progress_flags.hpp"
#include "data/Items.hpp"
#include "data/Bonus_Levels.hpp"
#include "data/Drives.hpp"
#include "data/Anchors.hpp"
#include "data/Levels.hpp"
#include "util/Utils.hpp"
#include "inventory.hpp"


class Checks_Other {
private:
    // TODO: replace these with a simple vector of all accessed check addresses
    // if an address has already been accessed, its value must not be uses again.
    static inline uint8_t highest_level_granted = 0;
    static inline std::map<uint16_t, uint8_t> workaround_progress_storage;
    static inline std::map<uint16_t, uint8_t> workaround_drivelvl_storage;

    static std::map<uint16_t, uint8_t> open_chests(std::map<uint16_t, uint8_t>& other_vals);
    static std::vector<uint16_t> from_chests(std::map<uint16_t, uint8_t> chests_added);
    static std::vector<uint16_t> from_drives(std::map<uint16_t, uint8_t>& other_vals);
    static std::vector<uint16_t> from_bonus_levels(std::map<uint16_t, uint8_t>& other_vals);
    static std::vector<uint16_t> from_levels(std::map<uint16_t, uint8_t>& other_vals);
    static std::vector<uint16_t> from_popups(std::map<uint16_t, uint8_t>& progress_added);
    static std::map<uint16_t, uint8_t> grant_progress(std::map<uint16_t, uint8_t>& other_vals);


public:
    static inline bool SHARE_PROGRESS = false;
    static inline bool SHARE_LEVELS = true;
    static inline bool SHARE_DRIVES = true;

    static std::vector<uint16_t> find_all_ids(std::map<uint16_t, uint8_t>& other_vals);

};
