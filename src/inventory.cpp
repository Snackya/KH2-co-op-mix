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

void Inventory::add_magic(uint16_t id)
{
    switch (id)
    {
    case 0x0015:    // Fire
        MemoryLib::WriteByte(Anchors::SAVE + 0x3594,
            (std::min)(MemoryLib::ReadByte(Anchors::SAVE + 0x3594) + 1, 3));
        break;
    case 0x0016:    // Blizzard
        MemoryLib::WriteByte(Anchors::SAVE + 0x3595,
            (std::min)(MemoryLib::ReadByte(Anchors::SAVE + 0x3595) + 1, 3));
        break;
    case 0x0017:    // Thunder
        MemoryLib::WriteByte(Anchors::SAVE + 0x3596,
            (std::min)(MemoryLib::ReadByte(Anchors::SAVE + 0x3596) + 1, 3));
        break;
    case 0x0018:    // Cure
        MemoryLib::WriteByte(Anchors::SAVE + 0x3597,
            (std::min)(MemoryLib::ReadByte(Anchors::SAVE + 0x3597) + 1, 3));
        break;
    case 0x0057:    // Magnet
        MemoryLib::WriteByte(Anchors::SAVE + 0x35CF,
            (std::min)(MemoryLib::ReadByte(Anchors::SAVE + 0x35CF) + 1, 3));
        break;
    case 0x0058:    // Reflect
        MemoryLib::WriteByte(Anchors::SAVE + 0x35D0,
            (std::min)(MemoryLib::ReadByte(Anchors::SAVE + 0x35D0) + 1, 3));
        break;
    default:
        std::cout << "Nothing matching ID " << std::hex << id << " found." << std::endl;
    }
}

// finds the items and abilities corresponding to the given IDs and add them ingame
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

        add_magic(id);
    }
}