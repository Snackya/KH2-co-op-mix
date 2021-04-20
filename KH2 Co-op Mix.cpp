// KH2 Co-op Mix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "MemoryLib.h"
#include <map>

using json = nlohmann::json;

//Addresses
static uint32_t WORLD_MOD = 0x0714DB8;

static inline uint64_t BaseAddress;
static inline DWORD PIdentifier = NULL;
static inline HANDLE PHandle = NULL;
static uint8_t goa_world_mod = 0x04;
json j_chests;
uint8_t current_world;


struct LOCATION_CHESTS {
    vector<uint32_t> addresses;
    vector<uint32_t> bitmasks;
    vector<uint8_t> values;
};

map<uint8_t, string> worlds_byte_string = {
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

int GoA_entered(uint8_t prev_world) {
    // JSON key string corresponding to WORLD_MOD byte value
    string prev_world_str = worlds_byte_string.at(prev_world);

    // get all chests of previous world
    LOCATION_CHESTS chests = currentAreaChests(prev_world_str);

    // map of bitmask addresses and their values
    // determines which chests have been opened
    map<uint32_t, uint32_t> chest_bm_vals;
    std::cout << "Chests of the area and their values:" << std::endl;
    for (uint32_t addr : chests.bitmasks)
    {
        std::cout << addr << " = "; print_byte(MemoryLib::ReadByte(addr));
        chest_bm_vals.insert({ addr, MemoryLib::ReadByte(addr) });
    }

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



int main()
{
    std::ifstream i("chests.json");
    j_chests = json::parse(i);

    //ch.addresses.push_back((uint32_t)(j_chests["PR"][0]["content"]));
    setup();
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
