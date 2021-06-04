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

static std::string GAME_VERSION = "PC";
static bool HOSTING = false;
static std::string SERVER_ADDR = "127.0.0.1";
static int PORT = 7356;

static uint8_t current_world;
static int refresh = 16;
static bool inside_goa = false;
static bool interrupt_loop = false;

void on_GoA_entered(uint8_t& world)
{
    // set the dream weapon for level checks
    std::cout << "GOA entered";
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
    uint16_t world_room = MemoryLib::ReadShort(Anchors::WORLD);
    uint8_t new_world = world_room & 0xff;
    if (new_world == 0x0F) return; //skip the world map.
    if (new_world == current_world && new_world != Anchors::GOA_WORLD_ID) return;  // world hasn't changed and isn't GOA. skip

    // GoA entered
    if (world_room == Anchors::GOA_WORLD_ROOM_ID && !inside_goa)
    {
        on_GoA_entered(current_world);
        inside_goa = true;
    }
    else if (world_room != Anchors::GOA_WORLD_ROOM_ID)
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

bool get_config()
{
    std::ifstream con_file("config.txt");
    if (con_file.is_open())
    {
        std::string line;
        while (getline(con_file, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            if(name == "HOST_ADDRESS") 
            { 
                SERVER_ADDR = value;
                if(value == "127.0.0.1") HOSTING = true;
            }
            else if(name == "PORT") PORT = stoi(value);
            else if(name == "VERSION") GAME_VERSION = value;
        }
        return 1;
    }
    else
    {
        std::cout << "config.txt not found." << std::endl;
        return 0;
    }
}

bool setup()
{
    // get config params
    //bool configured = get_config();
    //if (!configured)
    //{
    //    return 0;
    //}

    // set game anchors
    Anchors::set_anchors(GAME_VERSION);

    // init process handle
    bool attached = MemoryLib::AttachToGameVersion(GAME_VERSION);
    if (!attached)
    {
        std::cout << "Failed to attach to the " << GAME_VERSION << " version of the game.\n"
        << "Make sure the game is running and you selected the right version." << std::endl;
        return 0;
    }

    // init server
    //if (HOSTING)
    //{
    //    std::thread server_thread(Server::start, std::ref(PORT));   // bugged. crashes.
    //    std::cout << "Started server on port: " << PORT << std::endl;
    //}

    // init client
    bool connected = Http_Client::init(SERVER_ADDR, PORT);
    if (!connected)
    {
        std::cout << "Failed to connect to server at " << SERVER_ADDR << ":"
        << PORT << ".\n"
        << "Make sure the server is running and try again." << std::endl;
        return 0;
    }

    return 1;
}

void server_only()
{
    bool cnfg = get_config();
    std::cout << "Hosting server on port " << PORT << std::endl;
    Server::start(PORT);
}

int main()
{
    //server_only();
    bool setup_success = setup();
    if (!setup_success)
    {
        std::cout << "Setup failed. Aborting." << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Initialised successfully." << std::endl;
    }
    current_world = MemoryLib::ReadByte(Anchors::WORLD);
    loop();
}