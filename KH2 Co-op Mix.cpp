// KH2 Co-op Mix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Server.h"
#include "Http_Client.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include "MemoryLib.h"
#include <map>
#include <omp.h>
#include <string>
#include <chrono>
#include <thread>
#include "Popups.h"
#include "Chests.h"
#include "Abilities.h"
#include "Progress_flags.h"
#include "Items.h"
#include "Bonus_Levels.h"
#include "Drives.h"

//Addresses (default to PC)
static uint32_t WORLD_MOD = 0x0714DB8;  // PC
static uint32_t SAVE = 0x09A7070;       // PC
static uint32_t SYS3 = 0x2A59DB0;       // PC
static uint32_t BTL0 = 0x2A74840;       // PC

std::string MODE = "PS2";

static uint8_t goa_world_mod = 0x04;

std::string example_response = "7568,15|7569,219|7570,173|7571,75|7572,127|7573,16|7574,255|7575,255|7576,255|7577,70|7578,160|7579,0|9133,120|14084,252|14085,151|14086,255|14087,247|14088,239|14089,237|14090,70|14091,255|14092,254|14093,2";

static uint64_t BaseAddress;
static DWORD PIdentifier = NULL;
static HANDLE PHandle = NULL;
uint8_t current_world;

// TODO: replace these with a simple vector of all accessed check addresses
// if an address has already been accessed, its value must not be uses again.
std::map<uint16_t, uint8_t> workaround_progress_storage = {};
std::map<uint16_t, uint8_t> workaround_drivelvl_storage = {};

std::map<uint8_t, string> worlds_byte_string =
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
    {0x12, "TWTNW"},
};

vector<uint8_t> mask_to_values(uint8_t delta_val)
{
    vector<uint8_t> changed_bitmask_vals;
    for (int i = 0; i < 8; ++i)
    {
        if (delta_val >> i & 1)
        { 
            changed_bitmask_vals.push_back(1 << i);
        }
    }
    return changed_bitmask_vals;
}

// addr is either the inventory address or the bitmask address
void add_item(uint16_t addr, uint8_t val)
{
    // => inventory address
    if (val == 0)
    {
        uint8_t curr_val = MemoryLib::ReadByte(SAVE + addr);
        // prevent people from going back to 0 items. they might cry.
        if (curr_val < 255)
        {
            MemoryLib::WriteByte(SAVE + addr, curr_val + 1);
        }
    }
    // => bitmask address
    else
    {
        MemoryLib::WriteByte(SAVE + addr, MemoryLib::ReadByte(SAVE + addr) | val);
    }
}

void add_ability(uint16_t id)
{
    uint32_t ability_slot = SAVE + 0x2544;
    for (int i = 0; i <= 68; i += 2)
    {
        uint16_t ab = MemoryLib::ReadShort(ability_slot + i);
        if (ab == 0x0000)   // free slot
        {
            MemoryLib::WriteShort(ability_slot + i, id);
            break;
        }
    }
}

void add_magic(uint16_t id)
{
    switch (id)
    {
        case 0x0015:    // Fire
            MemoryLib::WriteByte(SAVE + 0x3594,
                std::max(MemoryLib::ReadByte(SAVE + 0x3594) + 1, 3));
            break;
        case 0x0016:    // Blizzard
            MemoryLib::WriteByte(SAVE + 0x3595,
                std::max(MemoryLib::ReadByte(SAVE + 0x3595) + 1, 3));
            break;
        case 0x0017:    // Thunder
            MemoryLib::WriteByte(SAVE + 0x3596,
                std::max(MemoryLib::ReadByte(SAVE + 0x3596) + 1, 3));
            break;
        case 0x0018:    // Cure
            MemoryLib::WriteByte(SAVE + 0x3597,
                std::max(MemoryLib::ReadByte(SAVE + 0x3597) + 1, 3));
            break;
        case 0x0057:    // Magnet
            MemoryLib::WriteByte(SAVE + 0x35CF,
                std::max(MemoryLib::ReadByte(SAVE + 0x35CF) + 1, 3));
            break;
        case 0x0058:    // Reflect
            MemoryLib::WriteByte(SAVE + 0x35D0,
                std::max(MemoryLib::ReadByte(SAVE + 0x35D0) + 1, 3));
            break;
        default:
            std::cout << "Nothing matching ID " << std::hex << id << " found." << std::endl;
    }
}

// finds the items and abilities corresponding to the given IDs and add them ingame
void get_stuff_from_ids(vector<uint16_t>& id_list)
{
    for (uint16_t id : id_list)
    {
        std::cout << std::hex << id << std::endl;
        auto it = items_id_invAddr.find(id);
        if(it != items_id_invAddr.end())
        {
            std::cout << "add inv item: " << std::hex << id << std::endl;
            add_item(it->second, 0);
            continue;
        }
        auto it2 = items_invBitmask.find(id);
        if (it2 != items_invBitmask.end())
        {
            std::cout << "add bitmask item: " << std::hex << id << std::endl;
            add_item(it2->second.first, it2->second.second);
            continue;
        }
        auto it3 = std::find(abilities.begin(), abilities.end(), id);
        if (it3 != abilities.end())
        {
            std::cout << "add ability: " << std::hex << id << std::endl;
            add_ability(id);
            continue;
        }

        add_magic(id);
    }
}

// actually find out *which* chests have been opened. the result is new_item_addr
void find_opened_chests(std::map<uint16_t, uint8_t>& chests_added)
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
                vector<uint8_t> new_vals = mask_to_values(added.second);

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

    get_stuff_from_ids(id_list);
}

//TODO: rewrite open_chests() to work for chests and flags
// open all chests of partner players, so items cannot be received twice
// overwrites bitmask values to open a range of chests
void open_chests(std::map<uint16_t, uint8_t>& other_vals)
{
    auto itr = other_vals.lower_bound(0x2300);
    auto upper_limit = other_vals.upper_bound(0x23FF);
    map<uint16_t, uint8_t> m_chests_added;
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

    find_opened_chests(m_chests_added);
}

std::map<uint16_t, uint8_t> get_world_checks(uint8_t world)
{
    // get the string representation of the world
    string prev_world_str = worlds_byte_string.at(world);
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

    // add the world's popup checks
    std::map<uint16_t, uint8_t> checks_popups;
    auto world_popups = popups[prev_world_str];
    for (auto pu : world_popups)
    {
        uint8_t val = MemoryLib::ReadByte(SAVE + pu.first);
        if (val > 0)
        {
            checks_chests.emplace(pu.first, val);
        }
    }
    checks.merge(checks_popups);

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

    return checks;
}

void grant_drive_level_checks(std::map<uint16_t, uint8_t>& other_vals)
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
        //MemoryLib::WriteByte(SAVE + ov_itr->first + 2, ov_itr->second);

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
    get_stuff_from_ids(id_list);
}

void grant_bonus_levels(std::map<uint16_t, uint8_t>& other_vals)
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

        vector<uint8_t> split_vals = mask_to_values(added);

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
                if(item1 != 0)  id_list.push_back(item1);
                if(item2 != 0)  id_list.push_back(item2);
            }
        }
    }
    get_stuff_from_ids(id_list);
}

void grant_popups(std::map<uint16_t, uint8_t>& progress_added)
{
    std::vector<uint16_t> id_list;

    // iterate over all areas and their chests
    for (auto area : popups)
    {
        // iterate over all newly added partner chests
        for (auto added : progress_added)
        {
            // get all (address, value) pairs for the current bitmask address
            auto it = area.second.equal_range(added.first);
            for (auto itr = it.first; itr != it.second; ++itr)
            {
                // split the value (byte) of the added chests into its bits to check against the bitmask lu-table
                vector<uint8_t> new_vals = mask_to_values(added.second);

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
    get_stuff_from_ids(id_list);
}

void grant_progress(std::map<uint16_t, uint8_t>& other_vals)
{
    auto itr = other_vals.lower_bound(0x1D00);
    auto upper_limit = other_vals.upper_bound(0x1EFF);
    map<uint16_t, uint8_t> progress_added;
    if(workaround_progress_storage.size() == 0)
    { 
        for (; itr != upper_limit; itr++)
        {
            uint8_t before = MemoryLib::ReadByte(SAVE + itr->first);
            uint8_t after = before | itr->second;
            uint8_t added = after - before;
            // perform a bit-wise OR at every address for own and partner value
            // bit-wise OR ensures the 2 values per address get proerply "merged"
            //MemoryLib::WriteByte(SAVE + itr->first, after);
            if (added != 0) {
                progress_added.emplace(itr->first, added);
                workaround_progress_storage[itr->first] = after;
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
            uint8_t after = before | itr->second;
            uint8_t added = after - before;
            if (added != 0) {
                progress_added.emplace(itr->first, added);
                workaround_progress_storage[itr->first] = after;
            }
        }
    }
    grant_popups(progress_added);
}

void redeem_checks(std::map<uint16_t, uint8_t>& other_vals)
{
    open_chests(other_vals);            // includes granting checks from chests
    grant_progress(other_vals);         // includes grant_popup()
    grant_bonus_levels(other_vals);
    grant_drive_level_checks(other_vals);
}

void world_changed()
{
    uint8_t new_world = MemoryLib::ReadByte(WORLD_MOD);
    
    if (new_world == 0x0F) return; //skip the world map.
    if (new_world == current_world) return;  // world hasn't changed. skip.
    
    // GoA entered
    if (new_world == goa_world_mod)
    {
        std::cout << "GoA entered from: " << worlds_byte_string.at(current_world) << std::endl;

        auto own_checks = get_world_checks(current_world);
        if (!own_checks.empty())
        {
            Http_Client::send_checks(own_checks);
        }
        auto checks = Http_Client::request_checks();
        redeem_checks(checks);

    }
    current_world = new_world;
}

void set_pcsx2_baseaddress()
{
    // over the horizon (valor form ability) address and expected value
    uint32_t oth_addr = 0x032EE36;
    uint16_t oth_val = 0x80F6;
    uint16_t val;
     
    // check multiple offsets until the read value matches the expected one.
    for (int i = 1; i < 8; ++i)
    {
        BaseAddress = 0x10000000 * i;
        vector<uint8_t> _buffer(2);
        ReadProcessMemory(PHandle, (void*)(BaseAddress + oth_addr), _buffer.data(), 2, 0);
        val = (_buffer[1] << 8) | _buffer[0];
        if (val == oth_val)
        {
            std::cout << "baseaddress is: " << BaseAddress << std::endl;
            break;
        }
    }
}

void set_anchors()
{
    if (MODE == "PC")
    {
        WORLD_MOD = 0x0714DB8;
        SAVE = 0x09A7070;
        SYS3 = 0x2A59DB0;
        BTL0 = 0x2A74840;
    }
    else if (MODE == "PS2")
    {
        WORLD_MOD = 0x032BAE0;
        SAVE = 0x032BB30;
        SYS3 = 0x1CCB300;
        BTL0 = 0x1CE5D80;
    }
}

int setup()
{
    if (MODE == "PC")
    {
        string _exec = "KINGDOM HEARTS II FINAL MIX.exe";
        PIdentifier = MemoryLib::FindProcessId(wstring(_exec.begin(), _exec.end()));
        PHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PIdentifier);
        BaseAddress = (uint64_t)MemoryLib::FindBaseAddr(PHandle, _exec);
    }
    else if (MODE == "PS2")
    {
        string _exec = "pcsx2.exe";
        PIdentifier = MemoryLib::FindProcessId(wstring(_exec.begin(), _exec.end()));
        PHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PIdentifier);
        set_pcsx2_baseaddress();
    }

    MemoryLib::SetBaseAddr(BaseAddress);
    MemoryLib::PHandle = PHandle;
    MemoryLib::PIdentifier = PIdentifier;

    set_anchors();

    return 1;
}

void loop()
{
    bool flag = true;
    int _refresh = 16;

    while (flag)
    {
        world_changed();

        //if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        //{

        //}
        
        std::this_thread::sleep_for(std::chrono::milliseconds(_refresh));
    }
}

void req(std::map<uint32_t, uint8_t> map_chests)
{
    std::string foo;
    std::cin >> foo;
    if (foo == "r")
    {
        //Http_Client::send_checks(map_chests);
        auto stuff = Http_Client::request_checks();
        if (!stuff.empty())
            for (auto shit : stuff)
            {
                std::cout << shit.first << " " << shit.second << std::endl;
            }
        req(map_chests);
    }
}

void foo(int bar)
{
    std::cout << bar;
}

int main()
{
    //Server::start(7356);
    std::cout << "Mode?: ";
    std::cin >> MODE;
    setup();
    Http_Client::init("127.0.0.1:7356");
    current_world = MemoryLib::ReadByte(WORLD_MOD);
    loop();
}