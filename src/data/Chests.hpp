#pragma once
#include <map>
#include <string>

// { "world",
//      {chest opened status bitmask addr, {bitmask val, chest content addr} }
// }
static inline std::map <std::string, std::multimap<uint16_t, std::pair<uint8_t, uint32_t>>> chests =
{
	{
		"100AW",
		{
			{0x23c9, {0x80, 0x14712}},		//Pooh Bear's House, 100 Acre Wood Map
			{0x23b5, {0x10, 0x1471e}},		//Pooh Bear's House, AP Boost
			{0x23b5, {0x20, 0x1472a}},		//Pooh Bear's House, Mythril Stone
			{0x23b6, {0x10, 0x14736}},		//Piglet's House, Defense Boost
			{0x23b6, {0x4, 0x14742}},		//Piglet's House, AP Boost
			{0x23b6, {0x8, 0x1474e}},		//Piglet's House, Mythril Gem
			{0x23ca, {0x1, 0x1475a}},		//Rabbit's House, Draw Ring
			{0x23b5, {0x80, 0x14766}},		//Rabbit's House, Mythril Crystal
			{0x23b6, {0x1, 0x14772}},		//Rabbit's House, AP Boost
			{0x23b6, {0x20, 0x1477e}},		//Kanga's House, AP Boost
			{0x23b6, {0x40, 0x1478a}},		//Kanga's House, Orichalcum
			{0x23b6, {0x80, 0x14796}},		//Kanga's House, Magic Boost
			{0x23b7, {0x2, 0x147a2}},		//The Spooky Cave, Mythril Gem
			{0x23b7, {0x4, 0x147ae}},		//The Spooky Cave, AP Boost
			{0x23b7, {0x8, 0x147ba}},		//The Spooky Cave, Orichalcum
			{0x23b7, {0x10, 0x147c6}},		//The Spooky Cave, Guard Recipe
			{0x23b7, {0x40, 0x147d2}},		//The Spooky Cave, Mythril Crystal
			{0x23b7, {0x80, 0x147de}},		//The Spooky Cave, AP Boost
			{0x23c9, {0x40, 0x147ea}},		//Starry Hill, Cosmic Ring
			{0x23b5, {0x2, 0x147f6}}		//Starry Hill, Style Recipe
		}
	},
	{
		"AG",
		{
			{0x23af, {0x8, 0x14526}},		//Agrabah, Dark Shard
			{0x23af, {0x10, 0x14532}},		//Agrabah, Mythril Shard
			{0x23af, {0x20, 0x1453e}},		//Agrabah, Hi-Potion
			{0x23af, {0x40, 0x1454a}},		//Agrabah, AP Boost
			{0x23af, {0x80, 0x14556}},		//Agrabah, Mythril Stone
			{0x23b0, {0x1, 0x14562}},		//Agrabah, Mythril Shard
			{0x23da, {0x8, 0x1456e}},		//Agrabah, Serenity Shard
			{0x23b0, {0x2, 0x1457a}},		//Bazaar, Mythril Gem
			{0x23b0, {0x4, 0x14586}},		//Bazaar, Power Shard
			{0x23b0, {0x8, 0x14592}},		//Bazaar, Hi-Potion
			{0x23b0, {0x10, 0x1459e}},		//Bazaar, AP Boost
			{0x23b0, {0x20, 0x145aa}},		//Bazaar, Mythril Shard
			{0x23b0, {0x40, 0x145b6}},		//Palace Walls, Skill Ring
			{0x23db, {0x20, 0x145c2}},		//Palace Walls, Mythril Stone
			{0x23b0, {0x80, 0x145ce}},		//The Cave of Wonders: Entrance, Power Stone
			{0x23b1, {0x1, 0x145da}},		//The Cave of Wonders: Entrance, Mythril Shard
			{0x23b1, {0x4, 0x145e6}},		//The Cave of Wonders: Valley of Stone, Mythril Stone
			{0x23b1, {0x8, 0x145f2}},		//The Cave of Wonders: Valley of Stone, AP Boost
			{0x23b1, {0x10, 0x145fe}},		//The Cave of Wonders: Valley of Stone, Mythril Shard
			{0x23b1, {0x20, 0x1460a}},		//The Cave of Wonders: Valley of Stone, Hi-Potion
			{0x23d8, {0x80, 0x14616}},		//The Cave of Wonders: Chasm of Challenges, The Cave of Wonders Map
			{0x23b1, {0x40, 0x14622}},		//The Cave of Wonders: Chasm of Challenges, AP Boost
			{0x23da, {0x10, 0x1462e}},		//The Cave of Wonders: Treasure Room, AP Boost
			{0x23da, {0x20, 0x1463a}},		//The Cave of Wonders: Treasure Room, Serenity Gem
			{0x23b1, {0x2, 0x14646}},		//Ruined Chamber, Torn Pages
			{0x23d8, {0x40, 0x14652}}		//Ruined Chamber, Ruins Map
		}
	},
	{
		"BC",
		{
			{0x23bb, {0x20, 0x148f2}},		//Courtyard (BC), AP Boost
			{0x23bb, {0x40, 0x148fe}},		//Courtyard (BC), Hi-Potion
			{0x23da, {0x80, 0x1490a}},		//Courtyard (BC), Mythril Shard
			{0x23bb, {0x4, 0x14916}},		//Belle's Room, Castle Map
			{0x23bb, {0x8, 0x14922}},		//Belle's Room, Mega-Recipe
			{0x23bb, {0x80, 0x1492e}},		//The East Wing, Mythril Shard
			{0x23bc, {0x1, 0x1493a}},		//The East Wing, Tent
			{0x23bc, {0x2, 0x14946}},		//The West Hall, Hi-Potion
			{0x23bc, {0x4, 0x14952}},		//The West Hall, Mythril Shard
			{0x23bc, {0x8, 0x1495e}},		//The West Hall, Power Shard
			{0x23bc, {0x10, 0x1496a}},		//The West Hall, Mythril Shard
			{0x23bc, {0x20, 0x14976}},		//The West Hall, AP Boost
			{0x23db, {0x1, 0x14982}},		//The West Hall, Bright Stone
			{0x23bd, {0x1, 0x1498e}},		//Dungeon, Basement Map
			{0x23bd, {0x2, 0x1499a}},		//Dungeon, AP Boost
			{0x23bd, {0x4, 0x149a6}},		//Secret Passage, Mythril Shard
			{0x23bd, {0x20, 0x149b2}},		//Secret Passage, Hi-Potion
			{0x23bd, {0x8, 0x149be}},		//Secret Passage, Lucid Shard
			{0x23bc, {0x40, 0x149ca}},		//The West Wing, Mythril Shard
			{0x23bc, {0x80, 0x149d6}},		//The West Wing, Tent
			{0x23bb, {0x10, 0x149e2}}		//Beast's Room, Blazing Shard
		}
	},
	{
		"DC",
		{
			{0x23b2, {0x1, 0x1465e}},		//Cornerstone Hill, Cornerstone Hill Map
			{0x23b2, {0x2, 0x1466a}},		//Cornerstone Hill, Frost Shard
			{0x23b2, {0x8, 0x14676}},		//Pier, Mythril Shard
			{0x23b2, {0x10, 0x14682}},		//Pier, Hi-Potion
			{0x23b2, {0x20, 0x1468e}},		//Waterway, Mythril Stone
			{0x23b2, {0x40, 0x1469a}},		//Waterway, AP Boost
			{0x23b2, {0x80, 0x146a6}},		//Waterway, Frost Stone
			{0x23b4, {0x2, 0x146b2}},		//Courtyard (DC), Mythril Shard
			{0x23b4, {0x4, 0x146be}},		//Courtyard (DC), Star Recipe
			{0x23b4, {0x8, 0x146ca}},		//Courtyard (DC), AP Boost
			{0x23b4, {0x10, 0x146d6}},		//Courtyard (DC), Mythril Stone
			{0x23b4, {0x20, 0x146e2}},		//Courtyard (DC), Blazing Stone
			{0x23b4, {0x40, 0x146ee}},		//Courtyard (DC), Blazing Shard
			{0x23b4, {0x80, 0x146fa}},		//Courtyard (DC), Mythril Shard
			{0x23b4, {0x1, 0x14706}}		//Library, Torn Pages
		}
	},
	{
		"HB",
		{
			{0x23c6, {0x2, 0x14c3a}},		//Borough, Drive Recovery
			{0x23c6, {0x4, 0x14c46}},		//Borough, AP Boost
			{0x23c6, {0x8, 0x14c52}},		//Borough, Hi-Potion
			{0x23c8, {0x80, 0x14c5e}},		//Borough, Mythril Shard
			{0x23db, {0x2, 0x14c6a}},		//Borough, Dark Shard
			{0x23c9, {0x10, 0x14c76}},		//Postern, Castle Perimeter Map
			{0x23c5, {0x10, 0x14c82}},		//Postern, Mythril Gem
			{0x23c5, {0x20, 0x14c8e}},		//Postern, AP Boost
			{0x23c6, {0x80, 0x14c9a}},		//Corridors, Mythril Stone
			{0x23c7, {0x1, 0x14ca6}},		//Corridors, Mythril Crystal
			{0x23c7, {0x2, 0x14cb2}},		//Corridors, Dark Crystal
			{0x23c9, {0x2, 0x14cbe}},		//Corridors, AP Boost
			{0x23c4, {0x80, 0x14cca}},		//Ansem's Study, Skill Recipe
			{0x23c4, {0x40, 0x14cd6}},		//Ansem's Study, Ukulele Charm
			{0x23c9, {0x8, 0x14ce2}},		//Restoration Site, Moon Recipe
			{0x23db, {0x4, 0x14cee}},		//Restoration Site, AP Boost
			{0x23c4, {0x4, 0x14cfa}},		//Crystal Fissure, Torn Pages
			{0x23d9, {0x2, 0x14d06}},		//Crystal Fissure, The Great Maw Map
			{0x23c4, {0x8, 0x14d12}},		//Crystal Fissure, Energy Crystal
			{0x23c4, {0x10, 0x14d1e}},		//Crystal Fissure, AP Boost
			{0x23d9, {0x8, 0x14d2a}},		//Postern, Gull Wing
			{0x23c9, {0x20, 0x14d36}}		//Heartless Manufactory, Cosmic Chain
		}
	},
	{
		"HT",
		{
			{0x23c0, {0x4, 0x14a96}},		//Graveyard, Mythril Shard
			{0x23c0, {0x8, 0x14aa2}},		//Graveyard, Serenity Gem
			{0x23c0, {0x2, 0x14aae}},		//Dr. Finkelstein's Lab, Halloween Town Map
			{0x23bf, {0x80, 0x14aba}},		//Halloween Town Square, Mythril Stone
			{0x23c0, {0x1, 0x14ac6}},		//Halloween Town Square, Energy Shard
			{0x23c0, {0x10, 0x14ad2}},		//Hinterlands, Lightning Shard
			{0x23c0, {0x20, 0x14ade}},		//Hinterlands, Mythril Stone
			{0x23c0, {0x40, 0x14aea}},		//Hinterlands, AP Boost
			{0x23c1, {0x1, 0x14af6}},		//Candy Cane Lane, Mega-Potion
			{0x23c1, {0x2, 0x14b02}},		//Candy Cane Lane, Mythril Gem
			{0x23c1, {0x4, 0x14b0e}},		//Candy Cane Lane, Lightning Stone
			{0x23c1, {0x8, 0x14b1a}},		//Candy Cane Lane, Mythril Stone
			{0x23c1, {0x40, 0x14b26}},		//Santa's House, Christmas Town Map
			{0x23c1, {0x10, 0x14b32}}		//Santa's House, AP Boost
		}
	},
	{
		"LOD",
		{
			{0x23d9, {0x80, 0x14436}},		//Bamboo Grove, Ether
			{0x23da, {0x1, 0x14442}},		//Bamboo Grove, Mythril Shard
			{0x23ad, {0x2, 0x1444e}},		//Checkpoint, Hi-Potion
			{0x23ad, {0x4, 0x1445a}},		//Checkpoint, Mythril Shard
			{0x23ad, {0x8, 0x14466}},		//Mountain Trail, Lightning Shard
			{0x23ad, {0x10, 0x14472}},		//Mountain Trail, Recovery Recipe
			{0x23ad, {0x20, 0x1447e}},		//Mountain Trail, Ether
			{0x23ad, {0x40, 0x1448a}},		//Mountain Trail, Mythril Shard
			{0x23ad, {0x80, 0x14496}},		//Village Cave, AP Boost
			{0x23ae, {0x1, 0x144a2}},		//Village Cave, Dark Shard
			{0x23ae, {0x2, 0x144ae}},		//Ridge, Frost Shard
			{0x23ae, {0x4, 0x144ba}},		//Ridge, AP Boost
			{0x23ae, {0x8, 0x144c6}},		//Throne Room, Torn Pages
			{0x23ae, {0x10, 0x144d2}},		//Throne Room, Palace Map
			{0x23ae, {0x20, 0x144de}},		//Throne Room, AP Boost
			{0x23ae, {0x40, 0x144ea}},		//Throne Room, Queen Recipe
			{0x23ae, {0x80, 0x144f6}},		//Throne Room, AP Boost
			{0x23af, {0x1, 0x14502}},		//Throne Room, Ogre Shield
			{0x23af, {0x2, 0x1450e}},		//Throne Room, Mythril Crystal
			{0x23af, {0x4, 0x1451a}}		//Throne Room, Orichalcum
		}
	},
	{
		"OC",
		{
			{0x23b8, {0x1, 0x14802}},		//Underworld Entrance, Power Boost
			{0x23b9, {0x40, 0x1480e}},		//Cave of the Dead: Passage, Mythril Shard
			{0x23b9, {0x80, 0x1481a}},		//Cave of the Dead: Passage, Mythril Stone
			{0x23ba, {0x1, 0x14826}},		//Cave of the Dead: Passage, Ether
			{0x23ba, {0x2, 0x14832}},		//Cave of the Dead: Passage, AP Boost
			{0x23ba, {0x4, 0x1483e}},		//Cave of the Dead: Passage, Hi-Potion
			{0x23b8, {0x10, 0x1484a}},		//Cave of the Dead: Inner Chamber, Underworld Map
			{0x23b8, {0x8, 0x14856}},		//Cave of the Dead: Inner Chamber, Mythril Shard
			{0x23b8, {0x20, 0x14862}},		//Underworld Caverns: Entrance, Lucid Shard
			{0x23b8, {0x40, 0x1486e}},		//Underworld Caverns: Entrance, AP Boost
			{0x23da, {0x40, 0x1487a}},		//Underworld Caverns: Entrance, Mythril Shard
			{0x23ba, {0x8, 0x14886}},		//Underworld Caverns: The Lost Road, Bright Shard
			{0x23ba, {0x10, 0x14892}},		//Underworld Caverns: The Lost Road, Ether
			{0x23ba, {0x20, 0x1489e}},		//Underworld Caverns: The Lost Road, Mythril Shard
			{0x23ba, {0x40, 0x148aa}},		//Underworld Caverns: The Lost Road, Mythril Stone
			{0x23ba, {0x80, 0x148b6}},		//Underworld Caverns: Atrium, Lucid Stone
			{0x23bb, {0x1, 0x148c2}},		//Underworld Caverns: Atrium, AP Boost
			{0x23b9, {0x10, 0x148ce}},		//The Lock, Caverns Map
			{0x23b9, {0x1, 0x148da}},		//The Lock, Mythril Shard
			{0x23b9, {0x4, 0x148e6}}		//The Lock, AP Boost
		}
	},
	{
		"PL",
		{
			{0x23d9, {0x10, 0x14d42}},		//Gorge, Savannah Map
			{0x23cf, {0x1, 0x14d4e}},		//Gorge, Dark Gem
			{0x23cf, {0x2, 0x14d5a}},		//Gorge, Mythril Stone
			{0x23ce, {0x20, 0x14d66}},		//Elephant Graveyard, Frost Gem
			{0x23ce, {0x40, 0x14d72}},		//Elephant Graveyard, Mythril Stone
			{0x23ce, {0x80, 0x14d7e}},		//Elephant Graveyard, Bright Stone
			{0x23db, {0x8, 0x14d8a}},		//Elephant Graveyard, AP Boost
			{0x23db, {0x10, 0x14d96}},		//Elephant Graveyard, Mythril Shard
			{0x23d0, {0x8, 0x14da2}},		//Pride Rock, Pride Rock Map
			{0x23cd, {0x10, 0x14dae}},		//Pride Rock, Mythril Stone
			{0x23cd, {0x20, 0x14dba}},		//Pride Rock, Serenity Crystal
			{0x23ce, {0x1, 0x14dc6}},		//Wildebeest Valley, Energy Stone
			{0x23ce, {0x2, 0x14dd2}},		//Wildebeest Valley, AP Boost
			{0x23ce, {0x4, 0x14dde}},		//Wildebeest Valley, Mythril Gem
			{0x23ce, {0x8, 0x14dea}},		//Wildebeest Valley, Mythril Stone
			{0x23ce, {0x10, 0x14df6}},		//Wildebeest Valley, Lucid Gem
			{0x23cf, {0x4, 0x14e02}},		//Wastelands, Mythril Shard
			{0x23cf, {0x8, 0x14e0e}},		//Wastelands, Serenity Gem
			{0x23cf, {0x10, 0x14e1a}},		//Wastelands, Mythril Stone
			{0x23cf, {0x20, 0x14e26}},		//Jungle, Serenity Gem
			{0x23cf, {0x40, 0x14e32}},		//Jungle, Mythril Stone
			{0x23cf, {0x80, 0x14e3e}},		//Jungle, Serenity Crystal
			{0x23d0, {0x1, 0x14e4a}},		//Oasis, Oasis Map
			{0x23d9, {0x20, 0x14e56}},		//Oasis, Torn Pages
			{0x23d0, {0x2, 0x14e62}}		//Oasis, AP Boost
		}
	},
	{
		"PR",
		{
			{0x23c2, {0x2, 0x14b3e}},		//Rampart, Naval Map
			{0x23c2, {0x4, 0x14b4a}},		//Rampart, Mythril Stone
			{0x23c2, {0x8, 0x14b56}},		//Rampart, Dark Shard
			{0x23c2, {0x10, 0x14b62}},		//Town, Dark Stone
			{0x23c2, {0x20, 0x14b6e}},		//Town, AP Boost
			{0x23c2, {0x40, 0x14b7a}},		//Town, Mythril Shard
			{0x23c2, {0x80, 0x14b86}},		//Town, Mythril Gem
			{0x23c3, {0x2, 0x14b92}},		//Isla de Muerta: Cave Mouth, Bright Shard
			{0x23c3, {0x4, 0x14b9e}},		//Isla de Muerta: Cave Mouth, Mythril Shard
			{0x23ca, {0x80, 0x14baa}},		//Isla de Muerta: Powder Store, AP Boost
			{0x23cb, {0x1, 0x14bb6}},		//Isla de Muerta: Powder Store, AP Boost
			{0x23c3, {0x10, 0x14bc2}},		//Isla de Muerta: Moonlight Nook, Mythril Shard
			{0x23c3, {0x20, 0x14bce}},		//Isla de Muerta: Moonlight Nook, Serenity Gem
			{0x23cb, {0x2, 0x14bda}},		//Isla de Muerta: Moonlight Nook, Power Stone
			{0x23c3, {0x8, 0x14be6}},		//Ship Graveyard: The Interceptor's Hold, Feather Charm
			{0x23c3, {0x40, 0x14bf2}},		//Ship Graveyard: Seadrift Keep, AP Boost
			{0x23c3, {0x80, 0x14bfe}},		//Ship Graveyard: Seadrift Keep, Orichalcum
			{0x23cb, {0x4, 0x14c0a}},		//Ship Graveyard: Seadrift Keep, Meteor Staff
			{0x23c4, {0x1, 0x14c16}},		//Ship Graveyard: Seadrift Row, Serenity Gem
			{0x23c4, {0x2, 0x14c22}},		//Ship Graveyard: Seadrift Row, King Recipe
			{0x23cb, {0x8, 0x14c2e}}		//Ship Graveyard: Seadrift Row, Mythril Crystal
		}
	},
	{
		"SP",
		{
			{0x23ca, {0x4, 0x149ee}},		//Pit Cell, Pit Cell Area Map
			{0x23bd, {0x40, 0x149fa}},		//Pit Cell, Mythril Crystal
			{0x23be, {0x2, 0x14a06}},		//Canyon, Dark Crystal
			{0x23be, {0x4, 0x14a12}},		//Canyon, Mythril Stone
			{0x23be, {0x8, 0x14a1e}},		//Canyon, Mythril Gem
			{0x23db, {0x40, 0x14a2a}},		//Canyon, Frost Crystal
			{0x23be, {0x10, 0x14a36}},		//I/O Tower: Hallway, Power Crystal
			{0x23be, {0x20, 0x14a42}},		//I/O Tower: Hallway, AP Boost
			{0x23bf, {0x2, 0x14a4e}},		//I/O Tower: Communications Room, I/O Tower Map
			{0x23da, {0x2, 0x14a5a}},		//I/O Tower: Communications Room, Gaia Belt
			{0x23bf, {0x10, 0x14a66}},		//Central Computer Mesa, AP Boost
			{0x23bf, {0x20, 0x14a72}},		//Central Computer Mesa, Orichalcum+
			{0x23bf, {0x40, 0x14a7e}},		//Central Computer Mesa, Cosmic Arts
			{0x23d9, {0x1, 0x14a8a}}		//Central Computer Mesa, Central Computer Core Map
		}
	},
	{
		"STT",
		{
			{0x23ca, {0x2, 0x14e6e}},		//Station of Serenity, Potion
			{0x23d7, {0x2, 0x14e7a}},		//Station of Calling, Potion
			{0x23d1, {0x20, 0x14e86}},		//Central Station (STT), Potion
			{0x23d1, {0x40, 0x14e92}},		//Central Station (STT), Hi-Potion
			{0x23d1, {0x80, 0x14e9e}},		//Central Station (STT), Potion
			{0x23d2, {0x8, 0x14eaa}},		//Sunset Terrace (STT), Ability Ring
			{0x23d2, {0x10, 0x14eb6}},		//Sunset Terrace (STT), Hi-Potion
			{0x23d2, {0x20, 0x14ec2}},		//Sunset Terrace (STT), Potion
			{0x23d2, {0x40, 0x14ece}},		//Sunset Terrace (STT), Potion
			{0x23d4, {0x4, 0x14eda}},		//Mansion: Foyer (STT), Hi-Potion
			{0x23d4, {0x8, 0x14ee6}},		//Mansion: Foyer (STT), Potion
			{0x23d4, {0x10, 0x14ef2}},		//Mansion: Foyer (STT), Potion
			{0x23d5, {0x1, 0x14efe}},		//Mansion: Dining Room (STT), Elven Bandanna
			{0x23d5, {0x2, 0x14f0a}},		//Mansion: Dining Room (STT), Potion
			{0x23d5, {0x10, 0x14f16}},		//Mansion: Library (STT), Hi-Potion
			{0x23d6, {0x1, 0x14f22}}		//Mansion: Basement Corridor (STT), Hi-Potion
		}
	},
	{
		"TT",
		{
			{0x23d4, {0x1, 0x14f2e}},		//The Old Mansion, Potion
			{0x23d4, {0x2, 0x14f3a}},		//The Old Mansion, Mythril Shard
			{0x23d3, {0x8, 0x14f46}},		//The Woods, Potion
			{0x23d3, {0x10, 0x14f52}},		//The Woods, Mythril Shard
			{0x23d3, {0x20, 0x14f5e}},		//The Woods, Hi-Potion
			{0x23d0, {0x20, 0x14f6a}},		//Tram Common, Hi-Potion
			{0x23d0, {0x40, 0x14f76}},		//Tram Common, AP Boost
			{0x23d0, {0x80, 0x14f82}},		//Tram Common, Tent
			{0x23d1, {0x1, 0x14f8e}},		//Tram Common, Mythril Shard
			{0x23d1, {0x2, 0x14f9a}},		//Tram Common, Potion
			{0x23d1, {0x4, 0x14fa6}},		//Tram Common, Mythril Shard
			{0x23d8, {0x20, 0x14fb2}},		//Tram Common, Potion
			{0x23d2, {0x1, 0x14fbe}},		//Central Station (TT), Tent
			{0x23d2, {0x2, 0x14fca}},		//Central Station (TT), Hi-Potion
			{0x23d2, {0x4, 0x14fd6}},		//Central Station (TT), Mythril Shard
			{0x23d6, {0x4, 0x14fe2}},		//The Tower, Potion
			{0x23d6, {0x8, 0x14fee}},		//The Tower, Hi-Potion
			{0x23db, {0x80, 0x14ffa}},		//The Tower, Ether
			{0x23d6, {0x10, 0x15006}},		//Tower: Entryway, Ether
			{0x23d6, {0x20, 0x15012}},		//Tower: Entryway, Mythril Shard
			{0x23d6, {0x40, 0x1501e}},		//Tower: Sorcerer's Loft, Tower Map
			{0x23d6, {0x80, 0x1502a}},		//Tower: Wardrobe, Mythril Stone
			{0x23d8, {0x1, 0x15036}},		//Underground Concourse, Mythril Gem
			{0x23d8, {0x2, 0x15042}},		//Underground Concourse, Orichalcum
			{0x23d8, {0x4, 0x1504e}},		//Underground Concourse, AP Boost
			{0x23d8, {0x8, 0x1505a}},		//Underground Concourse, Mythril Crystal
			{0x23d7, {0x40, 0x15066}},		//Tunnelway, Orichalcum
			{0x23d7, {0x80, 0x15072}},		//Tunnelway, Mythril Crystal
			{0x23d2, {0x80, 0x1507e}},		//Sunset Terrace (TT), Orichalcum+
			{0x23d3, {0x1, 0x1508a}},		//Sunset Terrace (TT), Mythril Shard
			{0x23d3, {0x2, 0x15096}},		//Sunset Terrace (TT), Mythril Crystal
			{0x23d3, {0x4, 0x150a2}},		//Sunset Terrace (TT), AP Boost
			{0x23d4, {0x20, 0x150ae}},		//Mansion: Foyer (TT), Mythril Crystal
			{0x23d4, {0x40, 0x150ba}},		//Mansion: Foyer (TT), Mythril Stone
			{0x23d4, {0x80, 0x150c6}},		//Mansion: Foyer (TT), Serenity Crystal
			{0x23d5, {0x4, 0x150d2}},		//Mansion: Dining Room (TT), Mythril Crystal
			{0x23d5, {0x8, 0x150de}},		//Mansion: Dining Room (TT), Mythril Stone
			{0x23d5, {0x20, 0x150ea}},		//Mansion: Library (TT), Orichalcum
			{0x23d6, {0x2, 0x150f6}},		//Mansion: Basement Corridor (TT), Ultimate Recipe
			//COR
			{0x23cd, {0x4, 0x151da}},		//Ruin and Creation's Passage, Orichalcum
			{0x23dc, {0x4, 0x151e6}},		//Cavern of Remembrance: Depths, AP Boost
			{0x23dc, {0x8, 0x151f2}},		//Cavern of Remembrance: Depths, Power Crystal
			{0x23dc, {0x10, 0x151fe}},		//Cavern of Remembrance: Depths, Frost Crystal
			{0x23dc, {0x20, 0x1520a}},		//Cavern of Remembrance: Depths, Manifest Illusion
			{0x23dc, {0x40, 0x15216}},		//Cavern of Remembrance: Depths, AP Boost
			{0x23dc, {0x80, 0x15222}},		//Cavern of Remembrance: Depths, Remembrance Gem
			{0x23dd, {0x1, 0x1522e}},		//Cavern of Remembrance: Mining Area, Serenity Gem
			{0x23dd, {0x2, 0x1523a}},		//Cavern of Remembrance: Mining Area, AP Boost
			{0x23dd, {0x4, 0x15246}},		//Cavern of Remembrance: Mining Area, Serenity Crystal
			{0x23dd, {0x8, 0x15252}},		//Cavern of Remembrance: Mining Area, Manifest Illusion
			{0x23dd, {0x10, 0x1525e}},		//Cavern of Remembrance: Mining Area, Serenity Gem
			{0x23dd, {0x20, 0x1526a}},		//Cavern of Remembrance: Mining Area, Dark Remembrance Map
			{0x23dd, {0x40, 0x15276}},		//Cavern of Remembrance: Engine Chamber, Serenity Crystal
			{0x23dd, {0x80, 0x15282}},		//Cavern of Remembrance: Engine Chamber, Remembrance Crystal
			{0x23de, {0x1, 0x1528e}},		//Cavern of Remembrance: Engine Chamber, AP Boost
			{0x23de, {0x2, 0x1529a}},		//Cavern of Remembrance: Engine Chamber, Manifest Illusion
			{0x23de, {0x4, 0x152a6}},		//Cavern of Remembrance: Mineshaft, AP Boost
			{0x23de, {0x8, 0x152b2}},		//Cavern of Remembrance: Mineshaft, AP Boost
			{0x23de, {0x10, 0x152be}},		//Cavern of Remembrance: Mineshaft, Depths of Remembrance Map
			{0x23de, {0x20, 0x152ca}},		//Cavern of Remembrance: Mineshaft, Power Boost
			{0x23de, {0x40, 0x152d6}}		//Cavern of Remembrance: Mineshaft, Magic Boost
		}
	},
	{
		"TWTNW",
		{
			{0x23cb, {0x10, 0x15102}},		//Fragment Crossing, Mythril Stone
			{0x23cb, {0x20, 0x1510e}},		//Fragment Crossing, Mythril Crystal
			{0x23cb, {0x40, 0x1511a}},		//Fragment Crossing, AP Boost
			{0x23cb, {0x80, 0x15126}},		//Fragment Crossing, Orichalcum
			{0x23cd, {0x8, 0x15132}},		//Memory's Skyscraper, Mythril Crystal
			{0x23dc, {0x1, 0x1513e}},		//Memory's Skyscraper, AP Boost
			{0x23dc, {0x2, 0x1514a}},		//Memory's Skyscraper, Mythril Stone
			{0x23ca, {0x20, 0x15156}},		//The Brink of Despair, Dark City Map
			{0x23da, {0x4, 0x15162}},		//The Brink of Despair, Orichalcum+
			{0x23cc, {0x1, 0x1516e}},		//Nothing's Call, Mythril Gem
			{0x23cc, {0x2, 0x1517a}},		//Nothing's Call, Orichalcum
			{0x23ca, {0x40, 0x15186}},		//Twilight's View, Cosmic Belt
			{0x23cc, {0x4, 0x15192}},		//Naught's Skyway, Mythril Gem
			{0x23cc, {0x8, 0x1519e}},		//Naught's Skyway, Orichalcum
			{0x23cc, {0x10, 0x151aa}},		//Naught's Skyway, Mythril Crystal
			{0x23cc, {0x80, 0x151b6}},		//Ruin and Creation's Passage, Mythril Stone
			{0x23cd, {0x1, 0x151c2}},		//Ruin and Creation's Passage, AP Boost
			{0x23cd, {0x2, 0x151ce}}		//Ruin and Creation's Passage, Mythril Crystal
		}
	}
};