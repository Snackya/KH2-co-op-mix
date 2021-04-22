// KH2 Co-op Mix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "MemoryLib.h"
#include <map>
#include <omp.h>
#include <string>

using json = nlohmann::json;

//Addresses
static uint32_t WORLD_MOD = 0x0714DB8;
static uint8_t goa_world_mod = 0x04;

static inline uint64_t BaseAddress;
static inline DWORD PIdentifier = NULL;
static inline HANDLE PHandle = NULL;
json j_chests;
json j_items;
uint8_t current_world;
std::multimap<uint32_t, std::pair<uint8_t, uint32_t>> m_maskVal_chestAddr;

// {id, (address, mask value)}
std::multimap<uint16_t, std::pair<uint32_t, uint8_t>> m_item_table;

struct LOCATION_CHESTS {
    vector<uint32_t> addresses;
    vector<uint32_t> bitmasks;
    vector<uint8_t> values;
};


void fill_chest_lookup_table()
{
    for (vector<json> chest_list : j_chests)
    {
        for (json chest : chest_list)
        {
            m_maskVal_chestAddr.insert(
                { strtoul(((string)chest["bitmask"]).c_str(), nullptr, 16),
                  std::pair(
                      strtoul(((string)chest["value"]).c_str(), nullptr, 16),
                      strtoul(((string)chest["content"]).c_str(), nullptr, 16)
                  )}
            );
        }
    }
}

void fill_item_lookup_table()
{
    for (json item : j_items["items"])
    {
        uint16_t id = item["id"];
        uint32_t addr;
        uint8_t val;
        if (item["inventory_address"] != 0)
        {
            addr = item["inventory_address"];
            val = 0;
        }
        else 
        {
            addr = item["bitmask_address"];
            val = item["bitmask_value"];
        }
       
        m_item_table.insert(
            {id,
            std::pair(addr, val)}
        );
    }
}

std::map<uint8_t, string> worlds_byte_string = {
    {0x12, "TWTNW"},
    {0x10, "PR"}
};

LOCATION_CHESTS currentAreaChests(string areaName)
{
    LOCATION_CHESTS lc;
    for (json fj : j_chests[areaName])
    {
        lc.addresses.push_back(
           strtoul(((string)fj["content"]).c_str(), nullptr, 16)
        );
        lc.bitmasks.push_back(
            strtoul(((string)fj["bitmask"]).c_str(), nullptr, 16)
        );
        lc.values.push_back(
            strtoul(((string)fj["value"]).c_str(), nullptr, 16)
        );
    }
    return lc;
}

void print_byte(uint8_t byte)
{
    std::cout << std::hex << (0xff & (unsigned int)byte) << std::endl;
}

vector<uint8_t> added_values(uint8_t delta_val)
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

void add_items_to_inv(vector<uint32_t>& chest_addresses)
{
    vector<uint32_t> item_vals;
    for (auto item_addr : chest_addresses)
    {
        item_vals.push_back(MemoryLib::ReadInt(item_addr));
    }
    for (uint32_t val : item_vals)
    {
        continue;
        //auto it = std::find(m_item_table.begin(), m_item_table.end(), val);
        //if (it != m_item_table.end())
        //{
        //    continue;
        //}
    }
}

// probably TODO: increase performance. maybe create new data structure for
void add_partner_items(std::map<uint32_t, uint8_t>& chests_added)
{
    vector<uint32_t> new_item_addr;
    // iterate over all new partner chests
    for (pair<int32_t, uint8_t> added : chests_added)
    {
        // get all (address, value) pairs for the current bitmask address
        auto it = m_maskVal_chestAddr.equal_range(added.first);
        for (auto itr = it.first; itr != it.second; ++itr)
        {
            // split the value (byte) of the added chests into its bits to check against the bitmask lu-table
            vector<uint8_t> new_vals = added_values(added.second);

            // split byte value matches one of the bitmasks. this chest has been opened.
            auto val_it = std::find(new_vals.begin(), new_vals.end(), itr->second.first);
            if (val_it != new_vals.end())
            {
                new_item_addr.push_back(itr->second.second);
            }
        }
    }

    add_items_to_inv(new_item_addr);

}

// open all chests of partner players, so items cannot be received twice
void open_partner_chests(std::map<uint32_t, uint8_t>& other_vals)
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
        //MemoryLib::WriteByte(item.first, after);

        m_chests_added.insert({item.first, added});
    }

    std::cout << "opening chest prints: \n";
    for (auto a : m_chests_added) {
        std::cout << a.first << "\t"; print_byte(a.second);
    }
    std::cout << "\n";
    add_partner_items(m_chests_added);
}



void receive_partner_values(std::map<uint32_t, uint8_t> other_vals)
{
    open_partner_chests(other_vals);
    add_partner_items(other_vals);
}

int GoA_entered(uint8_t prev_world) {
    // JSON key string corresponding to WORLD_MOD byte value
    string prev_world_str = worlds_byte_string.at(prev_world);

    // get all chests of previous world
    LOCATION_CHESTS chests = currentAreaChests(prev_world_str);

    // map of bitmask addresses and their values
    // determines which chests have been opened
    std::map<uint32_t, uint8_t> chest_bm_vals;
    for (uint32_t addr : chests.bitmasks)
    {
        chest_bm_vals.insert({ addr, MemoryLib::ReadByte(addr) });
    }

    // TODO: update world chests based on this map
    return 0;
}

int world_changed(uint8_t& current_world)
{
    uint8_t new_world = MemoryLib::ReadByte(WORLD_MOD);
    
    if (new_world == 0x0F) return 0; //skip the world map.
    if (new_world == current_world) return 0;  // world hasn't changed. skip.
    
    // GoA entered
    if (new_world == goa_world_mod)
    {
        std::cout << "GoA entered from: " << worlds_byte_string.at(current_world) << std::endl;
        GoA_entered(current_world);
    }
    current_world = new_world;
    return 1;
}

int setup()
{
    string _exec = "KINGDOM HEARTS II FINAL MIX.exe";
    PIdentifier = MemoryLib::FindProcessId(wstring(_exec.begin(), _exec.end()));
    PHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PIdentifier);
    BaseAddress = (uint64_t)MemoryLib::FindBaseAddr(PHandle, _exec);
    MemoryLib::SetBaseAddr(BaseAddress);
    MemoryLib::PHandle = PHandle;
    MemoryLib::PIdentifier = PIdentifier;

    return 1;
}

int loop()
{
    bool flag = true;

    while (flag)
    {
        world_changed(current_world);

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) flag = false;
        // if  area change. area is GOA


    }
    return 0;
}

struct ITEM {
    uint32_t id;
    string name;
};

void json_itemID_itemName();

int main()
{
    setup();
    std::ifstream i("chests.json");
    j_chests = json::parse(i);

    std::ifstream i2("items.json");
    j_items = json::parse(i2);

    fill_chest_lookup_table();
    fill_item_lookup_table();
    map<uint32_t, uint8_t> m;
    m.insert({ 0x9a9432 , 0x0a });
    m.insert({ 0x9a944f , 0x08 });
    //open_partner_chests(m);
    //current_world = MemoryLib::ReadByte(WORLD_MOD);
    //loop();
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

void json_itemID_itemName() {
    std::map<std::string, std::string> items;
    for (vector<json> chest_list : j_chests)
    {
        for (json chest : chest_list) {
            uint32_t addr = strtoul(((string)chest["content"]).c_str(), nullptr, 16);
            uint32_t val = MemoryLib::ReadShort(addr);

            items.insert(
                { std::to_string(val) , chest["name"] }
            );
        }
    }
    json j_items(items);
    std::ofstream o("items.json");
    o << j_items << std::endl;
}