// KH2 Co-op Mix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "server/Server.hpp"
#include "client/Http_Client.hpp"
#include <iostream>
#include <fstream>
#include "memory/MemoryLib.hpp"
#include <map>
#include <omp.h>
#include <string>
#include <chrono>
#include <thread>
#include "checks_other.hpp"
#include "checks_own.hpp"

static std::string MODE = "PC";

static uint8_t max_check_level = 50;

static uint8_t current_world;
static int refresh = 16;
static bool inside_goa = true;
static bool interrupt_loop = false;

std::string example_response = "7568,15|7569,219|7570,173|7571,75|7572,127|7573,16|7574,255|7575,255|7576,255|7577,70|7578,160|7579,0|9133,120|14084,252|14085,151|14086,255|14087,247|14088,239|14089,237|14090,70|14091,255|14092,254|14093,2";

void on_GoA_entered(uint8_t& world)
{
    // set the dream weapon for level checks
    if (weapon_offset) set_weapon_offset();

    auto own_checks = Checks_Own::get_world_checks(current_world);
    if (!own_checks.empty())
    {
        Http_Client::send_checks(own_checks);
    }

    auto checks = Http_Client::request_checks();
    auto ids = Checks_Other::find_all_ids(checks);
    Inventory::get_stuff_from_ids(ids);
}

void world_changed()
{
    uint16_t world_room = MemoryLib::ReadShort(WORLD);
    uint8_t new_world = world_room & 0xff;

    if (new_world == 0x0F) return; //skip the world map.
    if (new_world == current_world && new_world != GOA_WORLD_ID) return;  // world hasn't changed and isn't GOA. skip

    // GoA entered
    if (world_room == GOA_WORLD_ROOM_ID && !inside_goa)
    {
        on_GoA_entered(current_world);
        inside_goa = true;
    }
    else if (world_room != GOA_WORLD_ROOM_ID)
    {
        inside_goa = false;
    }

    //overwrite for next comparison
    current_world = new_world;
}

void loop()
{
    while (!interrupt_loop)
    {
        world_changed();
        std::this_thread::sleep_for(std::chrono::milliseconds(refresh));
    }
}

int main()
{
    //Server::start(7356);
    std::cout << "Mode?: ";
    std::cin >> MODE;
    MODE = "PC";
    MemoryLib::AttachToGameVersion(MODE);
    Http_Client::init("127.0.0.1:7356");
    current_world = MemoryLib::ReadByte(WORLD);
    loop();
}