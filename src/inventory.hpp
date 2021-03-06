#pragma once
#include "memory/MemoryLib.hpp"
#include "data/Items.hpp"
#include "data/Abilities.hpp"

class Inventory
{
private:
    static void add_item(uint16_t addr, uint8_t val);
    static void add_ability(uint16_t id);
    static void increase_lvl(uint16_t id, std::map<uint16_t, uint16_t> table, int max);

public:
    static void get_stuff_from_ids(vector<uint16_t>& id_list);
};