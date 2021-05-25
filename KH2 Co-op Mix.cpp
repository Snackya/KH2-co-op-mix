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

//Addresses
static uint32_t WORLD_MOD = 0x0714DB8;
static uint32_t SAVE = 0x09A7070;   // PC
static uint32_t SYS3 = 0x2A59DB0;   // PC
static uint8_t goa_world_mod = 0x04;

std::string example_response = "7568,15|7569,219|7570,173|7571,75|7572,127|7573,16|7574,255|7575,255|7576,255|7577,70|7578,160|7579,0|9133,120|14084,252|14085,151|14086,255|14087,247|14088,239|14089,237|14090,70|14091,255|14092,254|14093,2";

static uint64_t BaseAddress;
static DWORD PIdentifier = NULL;
static HANDLE PHandle = NULL;
uint8_t current_world;

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
void add_item_to_inventory(uint16_t addr, uint8_t val)
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
    for (int i = 0; i <= 68; i + 2)
    {
        uint16_t ab = MemoryLib::ReadShort(ability_slot);
        if (ab != 0x0000)   // free slot
        {
            MemoryLib::WriteShort(ability_slot, id);
            break;
        }
        else
        {
            std::cout << "Ran out of ability slots" << std::endl;
        }
    }
}

// finds the items and abilities corresponding to the given IDs and add them ingame
void get_stuff_from_ids(vector<uint16_t>& id_list)
{
    std::cout << id_list.size() << std::endl;
    for (uint16_t id : id_list)
    {
        std::cout << std::hex << id << std::endl;
        auto it = items_id_invAddr.find(id);
        if(it != items_id_invAddr.end())
        {
            add_item_to_inventory(it->second, 0);
            continue;
        }
        auto it2 = items_invBitmask.find(id);
        if (it2 != items_invBitmask.end())
        {
            add_item_to_inventory(it2->second.first, it2->second.second);
            continue;
        }
        auto it3 = std::find(abilities.begin(), abilities.end(), id);
        if (it3 != abilities.end())
        {
            add_ability(id);
            continue;
        }
        //std::cout << "Nothing matching ID " << id << " found." << std::endl;
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
        //MemoryLib::WriteByte(SAVE + itr->first, after);

        m_chests_added.emplace(itr->first, added);
    }

    find_opened_chests(m_chests_added);
}

std::map<uint16_t, uint8_t> get_world_checks(uint8_t world)
{
    // get the string representation of the world
    string prev_world_str = worlds_byte_string.at(world);
    std::map<uint16_t, uint8_t> checks;

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

    //add the progress flags for this world
    std::map<uint16_t, uint8_t> checks_progress_flags;
    auto world_progress = progress_flags[prev_world_str];
    for (auto flag : world_progress)
    {
        checks_progress_flags.emplace(flag, MemoryLib::ReadByte(SAVE + flag));
    }
    checks.merge(checks_progress_flags);

    return checks;
}

void grant_bonus_levels(std::map<uint16_t, uint8_t>& other_vals)
{
    auto ov_itr = other_vals.lower_bound(0x3700);
    auto upper_limit = other_vals.upper_bound(0x37FF);

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
                uint16_t item1 = MemoryLib::ReadShort(addr);
                uint16_t item2 = MemoryLib::ReadShort(addr + 2);
                std::vector ids = {item1, item2};
                get_stuff_from_ids(ids);
            }
        }
    }
}

void grant_popups(std::map<uint16_t, uint8_t>& progress_added)
{
    std::vector<uint16_t> id_list;
    for (auto added : progress_added) {
        std::cout << std::hex << added.first << "\t"; Util::print_byte(added.second);
    }
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
                    auto id = MemoryLib::ReadShort(itr->second.second);
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

    for (; itr != upper_limit; itr++)
    {
        uint8_t before = MemoryLib::ReadByte(SAVE + itr->first);
        uint8_t after = before | itr->second;
        uint8_t added = after - before;
        // perform a bit-wise OR at every address for own and partner value
        // bit-wise OR ensures the 2 values per address get proerply "merged"
        MemoryLib::WriteByte(SAVE + itr->first, after);
        if (added != 0) {
            progress_added.emplace(itr->first, added);
        }
    }
    grant_popups(progress_added);
}

void redeem_checks(std::map<uint16_t, uint8_t>& other_vals)
{
    //open_chests(other_vals);            // includes granting checks from chests
    grant_progress(other_vals);         // includes grant_popup()
    //grant_bonus_levels(other_vals);
}

void world_changed()
{
    uint8_t new_world = MemoryLib::ReadByte(WORLD_MOD);
    
    if (new_world == 0x0F) return; //skip the world map.
    if (new_world == current_world) return;  // world hasn't changed. skip.
    
    // GoA entered
    if (new_world == goa_world_mod)
    {
        //std::cout << "GoA entered from: " << worlds_byte_string.at(current_world) << std::endl;
        //std::cout << "World code: "; Util::print_byte(current_world);
        //auto own_checks = get_world_checks(current_world);
        //std::cout << "got the following checks:" << std::endl;
        //for (auto fak : own_checks)
        //{
        //    std::cout << std::hex << fak.first << ", "; Util::print_byte(fak.second);
        //}
        //std::cout << std::endl;
        //std::thread yourmom(Http_Client::send_checks, std::ref(own_checks));
        //yourmom.join();
        //auto checks = Http_Client::request_checks();
        //open_chests(checks);
        auto m = Util::string_to_map(example_response);
        redeem_checks(m);
    }
    current_world = new_world;
}

int setup()
{
    string _exec = "KINGDOM HEARTS II FINAL MIX.exe";
    PIdentifier = MemoryLib::FindProcessId(wstring(_exec.begin(), _exec.end()));
    //std::cout << "Enter KH2 PID: ";
    //std::cin >> PIdentifier;
    PHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PIdentifier);
    BaseAddress = (uint64_t)MemoryLib::FindBaseAddr(PHandle, _exec);
    MemoryLib::SetBaseAddr(BaseAddress);
    MemoryLib::PHandle = PHandle;
    MemoryLib::PIdentifier = PIdentifier;

    return 1;
}

void loop()
{
    bool flag = true;
    int _refresh = 16;

    while (flag)
    {
        world_changed();

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) flag = false;
        
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
    setup();
    //std::thread server_thread(Server::start, 8050);
    //std::map<uint32_t, uint8_t> map_chests;
    //map_chests.emplace(2543, 0xfa);
    //map_chests.emplace(5423423, 0x15);
    //map_chests.emplace(232111, 0x10);
    //auto str = Util::map_to_string(map_chests);
    //auto m = Util::string_to_map(str);
    //Http_Client::init("127.0.0.1:8050");
    current_world = MemoryLib::ReadByte(WORLD_MOD);
    loop();
}