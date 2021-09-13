#include "inventory.hpp"
#include "data/Anchors.hpp"


// addr is either the inventory address or the bitmask address
void Inventory::add_item(uint16_t addr, uint8_t val)
{
    // => inventory address
    if (val == 0)
    {
        uint8_t curr_val = MemoryLib::ReadByte(Anchors::SAVE + addr);
        // prevent people from going back to 0 items. they might cry.
        if (curr_val < 255)
        {
            MemoryLib::WriteByte(Anchors::SAVE + addr, curr_val + 1);
        }
    }
    // => bitmask address
    else
    {
        MemoryLib::WriteByte(
            Anchors::SAVE + addr,
            MemoryLib::ReadByte(Anchors::SAVE + addr) | val
        );
    }
}

void Inventory::add_ability(uint16_t id)
{
    uint32_t ability_slot = Anchors::SAVE + 0x2544;
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

void Inventory::increase_lvl(uint16_t id, std::map<uint16_t, uint16_t> table, int max=0)
{
    uint16_t addr = table[id];
    MemoryLib::WriteByte(
        Anchors::SAVE + addr,
        (std::min)(MemoryLib::ReadByte(Anchors::SAVE + addr) + 1, max)
    );
}

// finds the items, abilities and stat boosts corresponding to the given IDs and add them ingame
void Inventory::get_stuff_from_ids(vector<uint16_t>& id_list)
{
    for (uint16_t id : id_list)
    {
        auto it = items_id_invAddr.find(id);
        if (it != items_id_invAddr.end())
        {
            add_item(it->second, 0);
            continue;
        }
        auto it2 = items_invBitmask.find(id);
        if (it2 != items_invBitmask.end())
        {
            add_item(it2->second.first, it2->second.second);
            continue;
        }
        auto it3 = std::find(abilities.begin(), abilities.end(), id);
        if (it3 != abilities.end())
        {
            add_ability(id);
            continue;
        }
        auto it4 = magic_addrs.find(id);
        if (it4 != magic_addrs.end())
        {
            increase_lvl(id, magic_addrs, 3);
            continue;
        }
        auto it5 = stats_addrs.find(id);
        if (it5 != stats_addrs.end())
        {
            if (id == 0xFF02)
            {
                increase_lvl(id, magic_addrs, 9);   // drive gauge limited to lvl 9
            }
            else
            {
                increase_lvl(id, magic_addrs);      // don't know limit on other stats
            }
            continue;
        }
    }
}