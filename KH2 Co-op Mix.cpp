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
#include "items.h"

//Addresses
static uint32_t WORLD_MOD = 0x0714DB8;
static uint32_t SAVE = 0x09A7070; // PC
static uint8_t goa_world_mod = 0x04;

static uint64_t BaseAddress;
static DWORD PIdentifier = NULL;
static HANDLE PHandle = NULL;
uint8_t current_world;

std::map<uint8_t, string> worlds_byte_string = {
    {0x12, "TWTNW"},
    {0x10, "PR"}
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
void add_items_to_inventory(uint32_t addr, uint8_t val)
{
    // => inventory address
    if (val == 0)
    {
        uint8_t curr_val = MemoryLib::ReadByte(addr);
        // prevent people from going back to 0 items. they might cry.
        if (curr_val < 255)
        {
            MemoryLib::WriteByte(addr, curr_val + 1);

        }
    }
    // => bitmask address
    else
    {
        MemoryLib::WriteByte(addr, MemoryLib::ReadByte(addr) | val);
    }
}

// finds the items corresponding to a list of chests, which have been opened
void get_items_from_chests(vector<uint32_t>& chest_addresses)
{
    vector<uint16_t> id_list;
    for (auto item_addr : chest_addresses)
    {
        id_list.push_back(MemoryLib::ReadShort(item_addr));
    }
    for (uint16_t id : id_list)
    {
        auto it = items_id_invAddr.find(id);
        if(it != items_id_invAddr.end())
        {
            add_items_to_inventory(it->second, 0);
            continue;
        }
        auto itr = items_invBitmask.find(id);
        if (itr != items_invBitmask.end())
        {
            add_items_to_inventory(itr->second.first, itr->second.second);
        }
    }
}

// actually find out *which* chests have been opened. the result is new_item_addr
void find_opened_chests(std::map<uint32_t, uint8_t>& chests_added)
{
    std::vector<uint32_t> new_item_addr;

    // iterate over all areas and their chests
    for (auto area : chests)
    {
        // iterate over all newly added partner chests
        for (pair<int32_t, uint8_t> added : chests_added)
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
                    new_item_addr.push_back(itr->second.second);
                }
            }
        }
    }

    get_items_from_chests(new_item_addr);
}

// open all chests of partner players, so items cannot be received twice
// overwrites bitmask values to open a range of chests
void open_chests(std::map<uint32_t, uint8_t>& other_vals)
{
    map<uint32_t, uint8_t> m_chests_added;
    // loop over all "chest is open" address,status pairs
    for (pair<int32_t, uint8_t>item : other_vals)
    {
        uint8_t before = MemoryLib::ReadByte(item.first);
        uint8_t after = before | item.second;
        uint8_t added = after - before;
        // perform a bit-wise OR at every address for own and partner value
        // bit-wise OR ensures the 2 values per address get proerply "merged"
        MemoryLib::WriteByte(item.first, after);

        m_chests_added.insert({item.first, added});
    }

    find_opened_chests(m_chests_added);
}

std::map<uint32_t, uint8_t> get_world_chests(uint8_t world)
{
    // get the string representation of the world
    string prev_world_str = worlds_byte_string.at(world);

    // get all chests of previous world
    auto world_chests = chests[prev_world_str];

    // determines which chests have been opened
    std::map<uint32_t, uint8_t> chests_opened;
    for (auto chest : world_chests)
    {
        uint8_t val = MemoryLib::ReadByte(chest.first);
        if (val > 0)
        {
            chests_opened.insert({ chest.second.first, val });
        }
    }

    return chests_opened;
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
        auto own_checks = get_world_chests(current_world);
        std::thread yourmom(Http_Client::send_checks, std::ref(own_checks));
        yourmom.join();
        auto checks = Http_Client::request_checks();
        open_chests(checks);
    }
    current_world = new_world;
}

int setup()
{
    string _exec = "KINGDOM HEARTS II FINAL MIX.exe";
    //PIdentifier = MemoryLib::FindProcessId(wstring(_exec.begin(), _exec.end()));
    std::cout << "Enter KH2 PID: ";
    std::cin >> PIdentifier;
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
    std::map<uint32_t, uint8_t> map_chests;
    map_chests.emplace(2543, 0xfa);
    map_chests.emplace(5423423, 0x15);
    map_chests.emplace(232111, 0x10);
    //auto str = Util::map_to_string(map_chests);
    //auto m = Util::string_to_map(str);
    Http_Client::init("127.0.0.1:8050");
    current_world = MemoryLib::ReadByte(WORLD_MOD);
    loop();
}











// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


///////////////////////////////
//  LEGACY and UTILITY CODE  //
///////////////////////////////

//void json_itemID_itemName() {
//    std::map<std::string, std::string> items;
//    for (vector<json> chest_list : j_chests)
//    {
//        for (json chest : chest_list) {
//            uint32_t addr = strtoul(((string)chest["content"]).c_str(), nullptr, 16);
//            uint32_t val = MemoryLib::ReadShort(addr);
//
//            items.insert(
//                { std::to_string(val) , chest["name"] }
//            );
//        }
//    }
//    json j_items(items);
//    std::ofstream o("items.json");
//    o << j_items << std::endl;
//}