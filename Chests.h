#include <map>
#include <string>

// { "world",
//		 {chest opened status bitmask addr, {bitmask val, chest content addr} }
// }
static inline std::map <std::string, std::multimap<uint32_t, std::pair<uint8_t, uint32_t>>> chests =
{
	{
		"100AW",
		{
			{0x9a9439, {0x80, 0x2a6e4c2}},		//Pooh Bear's House, 100 Acre Wood Map
			{0x9a9425, {0x10, 0x2a6e4ce}},		//Pooh Bear's House, AP Boost
			{0x9a9425, {0x20, 0x2a6e4da}},		//Pooh Bear's House, Mythril Stone
			{0x9a9426, {0x10, 0x2a6e4e6}},		//Piglet's House, Defense Boost
			{0x9a9426, {0x4, 0x2a6e4f2}},		//Piglet's House, AP Boost
			{0x9a9426, {0x8, 0x2a6e4fe}},		//Piglet's House, Mythril Gem
			{0x9a943a, {0x1, 0x2a6e50a}},		//Rabbit's House, Draw Ring
			{0x9a9425, {0x80, 0x2a6e516}},		//Rabbit's House, Mythril Crystal
			{0x9a9426, {0x1, 0x2a6e522}},		//Rabbit's House, AP Boost
			{0x9a9426, {0x20, 0x2a6e52e}},		//Kanga's House, AP Boost
			{0x9a9426, {0x40, 0x2a6e53a}},		//Kanga's House, Orichalcum
			{0x9a9426, {0x80, 0x2a6e546}},		//Kanga's House, Magic Boost
			{0x9a9427, {0x2, 0x2a6e552}},		//The Spooky Cave, Mythril Gem
			{0x9a9427, {0x4, 0x2a6e55e}},		//The Spooky Cave, AP Boost
			{0x9a9427, {0x8, 0x2a6e56a}},		//The Spooky Cave, Orichalcum
			{0x9a9427, {0x10, 0x2a6e576}},		//The Spooky Cave, Guard Recipe
			{0x9a9427, {0x40, 0x2a6e582}},		//The Spooky Cave, Mythril Crystal
			{0x9a9427, {0x80, 0x2a6e58e}},		//The Spooky Cave, AP Boost
			{0x9a9439, {0x40, 0x2a6e59a}},		//Starry Hill, Cosmic Ring
			{0x9a9425, {0x2, 0x2a6e5a6}}		//Starry Hill, Style Recipe
		}
	},
	{
		"AG",
		{
			{0x9a941f, {0x8, 0x2a6e2d6}},		//Agrabah, Dark Shard
			{0x9a941f, {0x10, 0x2a6e2e2}},		//Agrabah, Mythril Shard
			{0x9a941f, {0x20, 0x2a6e2ee}},		//Agrabah, Hi-Potion
			{0x9a941f, {0x40, 0x2a6e2fa}},		//Agrabah, AP Boost
			{0x9a941f, {0x80, 0x2a6e306}},		//Agrabah, Mythril Stone
			{0x9a9420, {0x1, 0x2a6e312}},		//Agrabah, Mythril Shard
			{0x9a944a, {0x8, 0x2a6e31e}},		//Agrabah, Serenity Shard
			{0x9a9420, {0x2, 0x2a6e32a}},		//Bazaar, Mythril Gem
			{0x9a9420, {0x4, 0x2a6e336}},		//Bazaar, Power Shard
			{0x9a9420, {0x8, 0x2a6e342}},		//Bazaar, Hi-Potion
			{0x9a9420, {0x10, 0x2a6e34e}},		//Bazaar, AP Boost
			{0x9a9420, {0x20, 0x2a6e35a}},		//Bazaar, Mythril Shard
			{0x9a9420, {0x40, 0x2a6e366}},		//Palace Walls, Skill Ring
			{0x9a944b, {0x20, 0x2a6e372}},		//Palace Walls, Mythril Stone
			{0x9a9420, {0x80, 0x2a6e37e}},		//The Cave of Wonders: Entrance, Power Stone
			{0x9a9421, {0x1, 0x2a6e38a}},		//The Cave of Wonders: Entrance, Mythril Shard
			{0x9a9421, {0x4, 0x2a6e396}},		//The Cave of Wonders: Valley of Stone, Mythril Stone
			{0x9a9421, {0x8, 0x2a6e3a2}},		//The Cave of Wonders: Valley of Stone, AP Boost
			{0x9a9421, {0x10, 0x2a6e3ae}},		//The Cave of Wonders: Valley of Stone, Mythril Shard
			{0x9a9421, {0x20, 0x2a6e3ba}},		//The Cave of Wonders: Valley of Stone, Hi-Potion
			{0x9a9448, {0x80, 0x2a6e3c6}},		//The Cave of Wonders: Chasm of Challenges, The Cave of Wonders Map
			{0x9a9421, {0x40, 0x2a6e3d2}},		//The Cave of Wonders: Chasm of Challenges, AP Boost
			{0x9a944a, {0x10, 0x2a6e3de}},		//The Cave of Wonders: Treasure Room, AP Boost
			{0x9a944a, {0x20, 0x2a6e3ea}},		//The Cave of Wonders: Treasure Room, Serenity Gem
			{0x9a9421, {0x2, 0x2a6e3f6}},		//Ruined Chamber, Torn Pages
			{0x9a9448, {0x40, 0x2a6e402}}		//Ruined Chamber, Ruins Map
		}
	},
	{
		"BC",
		{
			{0x9a942b, {0x20, 0x2a6e6a2}},		//Courtyard (BC), AP Boost
			{0x9a942b, {0x40, 0x2a6e6ae}},		//Courtyard (BC), Hi-Potion
			{0x9a944a, {0x80, 0x2a6e6ba}},		//Courtyard (BC), Mythril Shard
			{0x9a942b, {0x4, 0x2a6e6c6}},		//Belle's Room, Castle Map
			{0x9a942b, {0x8, 0x2a6e6d2}},		//Belle's Room, Mega-Recipe
			{0x9a942b, {0x80, 0x2a6e6de}},		//The East Wing, Mythril Shard
			{0x9a942c, {0x1, 0x2a6e6ea}},		//The East Wing, Tent
			{0x9a942c, {0x2, 0x2a6e6f6}},		//The West Hall, Hi-Potion
			{0x9a942c, {0x4, 0x2a6e702}},		//The West Hall, Mythril Shard
			{0x9a942c, {0x8, 0x2a6e70e}},		//The West Hall, Power Shard
			{0x9a942c, {0x10, 0x2a6e71a}},		//The West Hall, Mythril Shard
			{0x9a942c, {0x20, 0x2a6e726}},		//The West Hall, AP Boost
			{0x9a944b, {0x1, 0x2a6e732}},		//The West Hall, Bright Stone
			{0x9a942d, {0x1, 0x2a6e73e}},		//Dungeon, Basement Map
			{0x9a942d, {0x2, 0x2a6e74a}},		//Dungeon, AP Boost
			{0x9a942d, {0x4, 0x2a6e756}},		//Secret Passage, Mythril Shard
			{0x9a942d, {0x20, 0x2a6e762}},		//Secret Passage, Hi-Potion
			{0x9a942d, {0x8, 0x2a6e76e}},		//Secret Passage, Lucid Shard
			{0x9a942c, {0x40, 0x2a6e77a}},		//The West Wing, Mythril Shard
			{0x9a942c, {0x80, 0x2a6e786}},		//The West Wing, Tent
			{0x9a942b, {0x10, 0x2a6e792}}		//Beast's Room, Blazing Shard
		}
	},
	{
		"DC",
		{
			{0x9a9422, {0x1, 0x2a6e40e}},		//Cornerstone Hill, Cornerstone Hill Map
			{0x9a9422, {0x2, 0x2a6e41a}},		//Cornerstone Hill, Frost Shard
			{0x9a9422, {0x8, 0x2a6e426}},		//Pier, Mythril Shard
			{0x9a9422, {0x10, 0x2a6e432}},		//Pier, Hi-Potion
			{0x9a9422, {0x20, 0x2a6e43e}},		//Waterway, Mythril Stone
			{0x9a9422, {0x40, 0x2a6e44a}},		//Waterway, AP Boost
			{0x9a9422, {0x80, 0x2a6e456}},		//Waterway, Frost Stone
			{0x9a9424, {0x2, 0x2a6e462}},		//Courtyard (DC), Mythril Shard
			{0x9a9424, {0x4, 0x2a6e46e}},		//Courtyard (DC), Star Recipe
			{0x9a9424, {0x8, 0x2a6e47a}},		//Courtyard (DC), AP Boost
			{0x9a9424, {0x10, 0x2a6e486}},		//Courtyard (DC), Mythril Stone
			{0x9a9424, {0x20, 0x2a6e492}},		//Courtyard (DC), Blazing Stone
			{0x9a9424, {0x40, 0x2a6e49e}},		//Courtyard (DC), Blazing Shard
			{0x9a9424, {0x80, 0x2a6e4aa}},		//Courtyard (DC), Mythril Shard
			{0x9a9424, {0x1, 0x2a6e4b6}}		//Library, Torn Pages
		}
	},
	{
		"HB",
		{
			{0x9a9436, {0x2, 0x2a6e9ea}},		//Borough, Drive Recovery
			{0x9a9436, {0x4, 0x2a6e9f6}},		//Borough, AP Boost
			{0x9a9436, {0x8, 0x2a6ea02}},		//Borough, Hi-Potion
			{0x9a9438, {0x80, 0x2a6ea0e}},		//Borough, Mythril Shard
			{0x9a944b, {0x2, 0x2a6ea1a}},		//Borough, Dark Shard
			{0x9a9439, {0x10, 0x2a6ea26}},		//Postern, Castle Perimeter Map
			{0x9a9435, {0x10, 0x2a6ea32}},		//Postern, Mythril Gem
			{0x9a9435, {0x20, 0x2a6ea3e}},		//Postern, AP Boost
			{0x9a9436, {0x80, 0x2a6ea4a}},		//Corridors, Mythril Stone
			{0x9a9437, {0x1, 0x2a6ea56}},		//Corridors, Mythril Crystal
			{0x9a9437, {0x2, 0x2a6ea62}},		//Corridors, Dark Crystal
			{0x9a9439, {0x2, 0x2a6ea6e}},		//Corridors, AP Boost
			{0x9a9434, {0x80, 0x2a6ea7a}},		//Ansem's Study, Skill Recipe
			{0x9a9434, {0x40, 0x2a6ea86}},		//Ansem's Study, Ukulele Charm
			{0x9a9439, {0x8, 0x2a6ea92}},		//Restoration Site, Moon Recipe
			{0x9a944b, {0x4, 0x2a6ea9e}},		//Restoration Site, AP Boost
			{0x9a9434, {0x4, 0x2a6eaaa}},		//Crystal Fissure, Torn Pages
			{0x9a9449, {0x2, 0x2a6eab6}},		//Crystal Fissure, The Great Maw Map
			{0x9a9434, {0x8, 0x2a6eac2}},		//Crystal Fissure, Energy Crystal
			{0x9a9434, {0x10, 0x2a6eace}},		//Crystal Fissure, AP Boost
			{0x9a9449, {0x8, 0x2a6eada}},		//Postern, Gull Wing
			{0x9a9439, {0x20, 0x2a6eae6}}		//Heartless Manufactory, Cosmic Chain
		}
	},
	{
		"HT",
		{
			{0x9a9430, {0x4, 0x2a6e846}},		//Graveyard, Mythril Shard
			{0x9a9430, {0x8, 0x2a6e852}},		//Graveyard, Serenity Gem
			{0x9a9430, {0x2, 0x2a6e85e}},		//Dr. Finkelstein's Lab, Halloween Town Map
			{0x9a942f, {0x80, 0x2a6e86a}},		//Halloween Town Square, Mythril Stone
			{0x9a9430, {0x1, 0x2a6e876}},		//Halloween Town Square, Energy Shard
			{0x9a9430, {0x10, 0x2a6e882}},		//Hinterlands, Lightning Shard
			{0x9a9430, {0x20, 0x2a6e88e}},		//Hinterlands, Mythril Stone
			{0x9a9430, {0x40, 0x2a6e89a}},		//Hinterlands, AP Boost
			{0x9a9431, {0x1, 0x2a6e8a6}},		//Candy Cane Lane, Mega-Potion
			{0x9a9431, {0x2, 0x2a6e8b2}},		//Candy Cane Lane, Mythril Gem
			{0x9a9431, {0x4, 0x2a6e8be}},		//Candy Cane Lane, Lightning Stone
			{0x9a9431, {0x8, 0x2a6e8ca}},		//Candy Cane Lane, Mythril Stone
			{0x9a9431, {0x40, 0x2a6e8d6}},		//Santa's House, Christmas Town Map
			{0x9a9431, {0x10, 0x2a6e8e2}}		//Santa's House, AP Boost
		}
	},
	{
		"LOD",
		{
			{0x9a9449, {0x80, 0x2a6e1e6}},		//Bamboo Grove, Ether
			{0x9a944a, {0x1, 0x2a6e1f2}},		//Bamboo Grove, Mythril Shard
			{0x9a941d, {0x2, 0x2a6e1fe}},		//Checkpoint, Hi-Potion
			{0x9a941d, {0x4, 0x2a6e20a}},		//Checkpoint, Mythril Shard
			{0x9a941d, {0x8, 0x2a6e216}},		//Mountain Trail, Lightning Shard
			{0x9a941d, {0x10, 0x2a6e222}},		//Mountain Trail, Recovery Recipe
			{0x9a941d, {0x20, 0x2a6e22e}},		//Mountain Trail, Ether
			{0x9a941d, {0x40, 0x2a6e23a}},		//Mountain Trail, Mythril Shard
			{0x9a941d, {0x80, 0x2a6e246}},		//Village Cave, AP Boost
			{0x9a941e, {0x1, 0x2a6e252}},		//Village Cave, Dark Shard
			{0x9a941e, {0x2, 0x2a6e25e}},		//Ridge, Frost Shard
			{0x9a941e, {0x4, 0x2a6e26a}},		//Ridge, AP Boost
			{0x9a941e, {0x8, 0x2a6e276}},		//Throne Room, Torn Pages
			{0x9a941e, {0x10, 0x2a6e282}},		//Throne Room, Palace Map
			{0x9a941e, {0x20, 0x2a6e28e}},		//Throne Room, AP Boost
			{0x9a941e, {0x40, 0x2a6e29a}},		//Throne Room, Queen Recipe
			{0x9a941e, {0x80, 0x2a6e2a6}},		//Throne Room, AP Boost
			{0x9a941f, {0x1, 0x2a6e2b2}},		//Throne Room, Ogre Shield
			{0x9a941f, {0x2, 0x2a6e2be}},		//Throne Room, Mythril Crystal
			{0x9a941f, {0x4, 0x2a6e2ca}}		//Throne Room, Orichalcum
		}
	},
	{
		"OC",
		{
			{0x9a9428, {0x1, 0x2a6e5b2}},		//Underworld Entrance, Power Boost
			{0x9a9429, {0x40, 0x2a6e5be}},		//Cave of the Dead: Passage, Mythril Shard
			{0x9a9429, {0x80, 0x2a6e5ca}},		//Cave of the Dead: Passage, Mythril Stone
			{0x9a942a, {0x1, 0x2a6e5d6}},		//Cave of the Dead: Passage, Ether
			{0x9a942a, {0x2, 0x2a6e5e2}},		//Cave of the Dead: Passage, AP Boost
			{0x9a942a, {0x4, 0x2a6e5ee}},		//Cave of the Dead: Passage, Hi-Potion
			{0x9a9428, {0x10, 0x2a6e5fa}},		//Cave of the Dead: Inner Chamber, Underworld Map
			{0x9a9428, {0x8, 0x2a6e606}},		//Cave of the Dead: Inner Chamber, Mythril Shard
			{0x9a9428, {0x20, 0x2a6e612}},		//Underworld Caverns: Entrance, Lucid Shard
			{0x9a9428, {0x40, 0x2a6e61e}},		//Underworld Caverns: Entrance, AP Boost
			{0x9a944a, {0x40, 0x2a6e62a}},		//Underworld Caverns: Entrance, Mythril Shard
			{0x9a942a, {0x8, 0x2a6e636}},		//Underworld Caverns: The Lost Road, Bright Shard
			{0x9a942a, {0x10, 0x2a6e642}},		//Underworld Caverns: The Lost Road, Ether
			{0x9a942a, {0x20, 0x2a6e64e}},		//Underworld Caverns: The Lost Road, Mythril Shard
			{0x9a942a, {0x40, 0x2a6e65a}},		//Underworld Caverns: The Lost Road, Mythril Stone
			{0x9a942a, {0x80, 0x2a6e666}},		//Underworld Caverns: Atrium, Lucid Stone
			{0x9a942b, {0x1, 0x2a6e672}},		//Underworld Caverns: Atrium, AP Boost
			{0x9a9429, {0x10, 0x2a6e67e}},		//The Lock, Caverns Map
			{0x9a9429, {0x1, 0x2a6e68a}},		//The Lock, Mythril Shard
			{0x9a9429, {0x4, 0x2a6e696}}		//The Lock, AP Boost
		}
	},
	{
		"PL",
		{
			{0x9a9449, {0x10, 0x2a6eaf2}},		//Gorge, Savannah Map
			{0x9a943f, {0x1, 0x2a6eafe}},		//Gorge, Dark Gem
			{0x9a943f, {0x2, 0x2a6eb0a}},		//Gorge, Mythril Stone
			{0x9a943e, {0x20, 0x2a6eb16}},		//Elephant Graveyard, Frost Gem
			{0x9a943e, {0x40, 0x2a6eb22}},		//Elephant Graveyard, Mythril Stone
			{0x9a943e, {0x80, 0x2a6eb2e}},		//Elephant Graveyard, Bright Stone
			{0x9a944b, {0x8, 0x2a6eb3a}},		//Elephant Graveyard, AP Boost
			{0x9a944b, {0x10, 0x2a6eb46}},		//Elephant Graveyard, Mythril Shard
			{0x9a9440, {0x8, 0x2a6eb52}},		//Pride Rock, Pride Rock Map
			{0x9a943d, {0x10, 0x2a6eb5e}},		//Pride Rock, Mythril Stone
			{0x9a943d, {0x20, 0x2a6eb6a}},		//Pride Rock, Serenity Crystal
			{0x9a943e, {0x1, 0x2a6eb76}},		//Wildebeest Valley, Energy Stone
			{0x9a943e, {0x2, 0x2a6eb82}},		//Wildebeest Valley, AP Boost
			{0x9a943e, {0x4, 0x2a6eb8e}},		//Wildebeest Valley, Mythril Gem
			{0x9a943e, {0x8, 0x2a6eb9a}},		//Wildebeest Valley, Mythril Stone
			{0x9a943e, {0x10, 0x2a6eba6}},		//Wildebeest Valley, Lucid Gem
			{0x9a943f, {0x4, 0x2a6ebb2}},		//Wastelands, Mythril Shard
			{0x9a943f, {0x8, 0x2a6ebbe}},		//Wastelands, Serenity Gem
			{0x9a943f, {0x10, 0x2a6ebca}},		//Wastelands, Mythril Stone
			{0x9a943f, {0x20, 0x2a6ebd6}},		//Jungle, Serenity Gem
			{0x9a943f, {0x40, 0x2a6ebe2}},		//Jungle, Mythril Stone
			{0x9a943f, {0x80, 0x2a6ebee}},		//Jungle, Serenity Crystal
			{0x9a9440, {0x1, 0x2a6ebfa}},		//Oasis, Oasis Map
			{0x9a9449, {0x20, 0x2a6ec06}},		//Oasis, Torn Pages
			{0x9a9440, {0x2, 0x2a6ec12}}		//Oasis, AP Boost
		}
	},
	{
		"PR",
		{
			{0x9a9432, {0x2, 0x2a6e8ee}},		//Rampart, Naval Map
			{0x9a9432, {0x4, 0x2a6e8fa}},		//Rampart, Mythril Stone
			{0x9a9432, {0x8, 0x2a6e906}},		//Rampart, Dark Shard
			{0x9a9432, {0x10, 0x2a6e912}},		//Town, Dark Stone
			{0x9a9432, {0x20, 0x2a6e91e}},		//Town, AP Boost
			{0x9a9432, {0x40, 0x2a6e92a}},		//Town, Mythril Shard
			{0x9a9432, {0x80, 0x2a6e936}},		//Town, Mythril Gem
			{0x9a9433, {0x2, 0x2a6e942}},		//Isla de Muerta: Cave Mouth, Bright Shard
			{0x9a9433, {0x4, 0x2a6e94e}},		//Isla de Muerta: Cave Mouth, Mythril Shard
			{0x9a943a, {0x80, 0x2a6e95a}},		//Isla de Muerta: Powder Store, AP Boost
			{0x9a943b, {0x1, 0x2a6e966}},		//Isla de Muerta: Powder Store, AP Boost
			{0x9a9433, {0x10, 0x2a6e972}},		//Isla de Muerta: Moonlight Nook, Mythril Shard
			{0x9a9433, {0x20, 0x2a6e97e}},		//Isla de Muerta: Moonlight Nook, Serenity Gem
			{0x9a943b, {0x2, 0x2a6e98a}},		//Isla de Muerta: Moonlight Nook, Power Stone
			{0x9a9433, {0x8, 0x2a6e996}},		//Ship Graveyard: The Interceptor's Hold, Feather Charm
			{0x9a9433, {0x40, 0x2a6e9a2}},		//Ship Graveyard: Seadrift Keep, AP Boost
			{0x9a9433, {0x80, 0x2a6e9ae}},		//Ship Graveyard: Seadrift Keep, Orichalcum
			{0x9a943b, {0x4, 0x2a6e9ba}},		//Ship Graveyard: Seadrift Keep, Meteor Staff
			{0x9a9434, {0x1, 0x2a6e9c6}},		//Ship Graveyard: Seadrift Row, Serenity Gem
			{0x9a9434, {0x2, 0x2a6e9d2}},		//Ship Graveyard: Seadrift Row, King Recipe
			{0x9a943b, {0x8, 0x2a6e9de}}		//Ship Graveyard: Seadrift Row, Mythril Crystal
		}
	},
	{
		"SP",
		{
			{0x9a943a, {0x4, 0x2a6e79e}},		//Pit Cell, Pit Cell Area Map
			{0x9a942d, {0x40, 0x2a6e7aa}},		//Pit Cell, Mythril Crystal
			{0x9a942e, {0x2, 0x2a6e7b6}},		//Canyon, Dark Crystal
			{0x9a942e, {0x4, 0x2a6e7c2}},		//Canyon, Mythril Stone
			{0x9a942e, {0x8, 0x2a6e7ce}},		//Canyon, Mythril Gem
			{0x9a944b, {0x40, 0x2a6e7da}},		//Canyon, Frost Crystal
			{0x9a942e, {0x10, 0x2a6e7e6}},		//I/O Tower: Hallway, Power Crystal
			{0x9a942e, {0x20, 0x2a6e7f2}},		//I/O Tower: Hallway, AP Boost
			{0x9a942f, {0x2, 0x2a6e7fe}},		//I/O Tower: Communications Room, I/O Tower Map
			{0x9a944a, {0x2, 0x2a6e80a}},		//I/O Tower: Communications Room, Gaia Belt
			{0x9a942f, {0x10, 0x2a6e816}},		//Central Computer Mesa, AP Boost
			{0x9a942f, {0x20, 0x2a6e822}},		//Central Computer Mesa, Orichalcum+
			{0x9a942f, {0x40, 0x2a6e82e}},		//Central Computer Mesa, Cosmic Arts
			{0x9a9449, {0x1, 0x2a6e83a}}		//Central Computer Mesa, Central Computer Core Map
		}
	},
	{
		"STT",
		{
			{0x9a943a, {0x2, 0x2a6ec1e}},		//Station of Serenity, Potion
			{0x9a9447, {0x2, 0x2a6ec2a}},		//Station of Calling, Potion
			{0x9a9441, {0x20, 0x2a6ec36}},		//Central Station (STT), Potion
			{0x9a9441, {0x40, 0x2a6ec42}},		//Central Station (STT), Hi-Potion
			{0x9a9441, {0x80, 0x2a6ec4e}},		//Central Station (STT), Potion
			{0x9a9442, {0x8, 0x2a6ec5a}},		//Sunset Terrace (STT), Ability Ring
			{0x9a9442, {0x10, 0x2a6ec66}},		//Sunset Terrace (STT), Hi-Potion
			{0x9a9442, {0x20, 0x2a6ec72}},		//Sunset Terrace (STT), Potion
			{0x9a9442, {0x40, 0x2a6ec7e}},		//Sunset Terrace (STT), Potion
			{0x9a9444, {0x4, 0x2a6ec8a}},		//Mansion: Foyer (STT), Hi-Potion
			{0x9a9444, {0x8, 0x2a6ec96}},		//Mansion: Foyer (STT), Potion
			{0x9a9444, {0x10, 0x2a6eca2}},		//Mansion: Foyer (STT), Potion
			{0x9a9445, {0x1, 0x2a6ecae}},		//Mansion: Dining Room (STT), Elven Bandanna
			{0x9a9445, {0x2, 0x2a6ecba}},		//Mansion: Dining Room (STT), Potion
			{0x9a9445, {0x10, 0x2a6ecc6}},		//Mansion: Library (STT), Hi-Potion
			{0x9a9446, {0x1, 0x2a6ecd2}}		//Mansion: Basement Corridor (STT), Hi-Potion
		}
	},
	{
		"TT",
		{
			{0x9a9444, {0x1, 0x2a6ecde}},		//The Old Mansion, Potion
			{0x9a9444, {0x2, 0x2a6ecea}},		//The Old Mansion, Mythril Shard
			{0x9a9443, {0x8, 0x2a6ecf6}},		//The Woods, Potion
			{0x9a9443, {0x10, 0x2a6ed02}},		//The Woods, Mythril Shard
			{0x9a9443, {0x20, 0x2a6ed0e}},		//The Woods, Hi-Potion
			{0x9a9440, {0x20, 0x2a6ed1a}},		//Tram Common, Hi-Potion
			{0x9a9440, {0x40, 0x2a6ed26}},		//Tram Common, AP Boost
			{0x9a9440, {0x80, 0x2a6ed32}},		//Tram Common, Tent
			{0x9a9441, {0x1, 0x2a6ed3e}},		//Tram Common, Mythril Shard
			{0x9a9441, {0x2, 0x2a6ed4a}},		//Tram Common, Potion
			{0x9a9441, {0x4, 0x2a6ed56}},		//Tram Common, Mythril Shard
			{0x9a9448, {0x20, 0x2a6ed62}},		//Tram Common, Potion
			{0x9a9442, {0x1, 0x2a6ed6e}},		//Central Station (TT), Tent
			{0x9a9442, {0x2, 0x2a6ed7a}},		//Central Station (TT), Hi-Potion
			{0x9a9442, {0x4, 0x2a6ed86}},		//Central Station (TT), Mythril Shard
			{0x9a9446, {0x4, 0x2a6ed92}},		//The Tower, Potion
			{0x9a9446, {0x8, 0x2a6ed9e}},		//The Tower, Hi-Potion
			{0x9a944b, {0x80, 0x2a6edaa}},		//The Tower, Ether
			{0x9a9446, {0x10, 0x2a6edb6}},		//Tower: Entryway, Ether
			{0x9a9446, {0x20, 0x2a6edc2}},		//Tower: Entryway, Mythril Shard
			{0x9a9446, {0x40, 0x2a6edce}},		//Tower: Sorcerer's Loft, Tower Map
			{0x9a9446, {0x80, 0x2a6edda}},		//Tower: Wardrobe, Mythril Stone
			{0x9a9448, {0x1, 0x2a6ede6}},		//Underground Concourse, Mythril Gem
			{0x9a9448, {0x2, 0x2a6edf2}},		//Underground Concourse, Orichalcum
			{0x9a9448, {0x4, 0x2a6edfe}},		//Underground Concourse, AP Boost
			{0x9a9448, {0x8, 0x2a6ee0a}},		//Underground Concourse, Mythril Crystal
			{0x9a9447, {0x40, 0x2a6ee16}},		//Tunnelway, Orichalcum
			{0x9a9447, {0x80, 0x2a6ee22}},		//Tunnelway, Mythril Crystal
			{0x9a9442, {0x80, 0x2a6ee2e}},		//Sunset Terrace (TT), Orichalcum+
			{0x9a9443, {0x1, 0x2a6ee3a}},		//Sunset Terrace (TT), Mythril Shard
			{0x9a9443, {0x2, 0x2a6ee46}},		//Sunset Terrace (TT), Mythril Crystal
			{0x9a9443, {0x4, 0x2a6ee52}},		//Sunset Terrace (TT), AP Boost
			{0x9a9444, {0x20, 0x2a6ee5e}},		//Mansion: Foyer (TT), Mythril Crystal
			{0x9a9444, {0x40, 0x2a6ee6a}},		//Mansion: Foyer (TT), Mythril Stone
			{0x9a9444, {0x80, 0x2a6ee76}},		//Mansion: Foyer (TT), Serenity Crystal
			{0x9a9445, {0x4, 0x2a6ee82}},		//Mansion: Dining Room (TT), Mythril Crystal
			{0x9a9445, {0x8, 0x2a6ee8e}},		//Mansion: Dining Room (TT), Mythril Stone
			{0x9a9445, {0x20, 0x2a6ee9a}},		//Mansion: Library (TT), Orichalcum
			{0x9a9446, {0x2, 0x2a6eea6}},		//Mansion: Basement Corridor (TT), Ultimate Recipe
			//COR
			{0x9a943d, {0x4, 0x2a6ef8a}},		//Ruin and Creation's Passage, Orichalcum
			{0x9a944c, {0x4, 0x2a6ef96}},		//Cavern of Remembrance: Depths, AP Boost
			{0x9a944c, {0x8, 0x2a6efa2}},		//Cavern of Remembrance: Depths, Power Crystal
			{0x9a944c, {0x10, 0x2a6efae}},		//Cavern of Remembrance: Depths, Frost Crystal
			{0x9a944c, {0x20, 0x2a6efba}},		//Cavern of Remembrance: Depths, Manifest Illusion
			{0x9a944c, {0x40, 0x2a6efc6}},		//Cavern of Remembrance: Depths, AP Boost
			{0x9a944c, {0x80, 0x2a6efd2}},		//Cavern of Remembrance: Depths, Remembrance Gem
			{0x9a944d, {0x1, 0x2a6efde}},		//Cavern of Remembrance: Mining Area, Serenity Gem
			{0x9a944d, {0x2, 0x2a6efea}},		//Cavern of Remembrance: Mining Area, AP Boost
			{0x9a944d, {0x4, 0x2a6eff6}},		//Cavern of Remembrance: Mining Area, Serenity Crystal
			{0x9a944d, {0x8, 0x2a6f002}},		//Cavern of Remembrance: Mining Area, Manifest Illusion
			{0x9a944d, {0x10, 0x2a6f00e}},		//Cavern of Remembrance: Mining Area, Serenity Gem
			{0x9a944d, {0x20, 0x2a6f01a}},		//Cavern of Remembrance: Mining Area, Dark Remembrance Map
			{0x9a944d, {0x40, 0x2a6f026}},		//Cavern of Remembrance: Engine Chamber, Serenity Crystal
			{0x9a944d, {0x80, 0x2a6f032}},		//Cavern of Remembrance: Engine Chamber, Remembrance Crystal
			{0x9a944e, {0x1, 0x2a6f03e}},		//Cavern of Remembrance: Engine Chamber, AP Boost
			{0x9a944e, {0x2, 0x2a6f04a}},		//Cavern of Remembrance: Engine Chamber, Manifest Illusion
			{0x9a944e, {0x4, 0x2a6f056}},		//Cavern of Remembrance: Mineshaft, AP Boost
			{0x9a944e, {0x8, 0x2a6f062}},		//Cavern of Remembrance: Mineshaft, AP Boost
			{0x9a944e, {0x10, 0x2a6f06e}},		//Cavern of Remembrance: Mineshaft, Depths of Remembrance Map
			{0x9a944e, {0x20, 0x2a6f07a}},		//Cavern of Remembrance: Mineshaft, Power Boost
			{0x9a944e, {0x40, 0x2a6f086}}		//Cavern of Remembrance: Mineshaft, Magic Boost
		}
	},
	{
		"TWTNW",
		{
			{0x9a943b, {0x10, 0x2a6eeb2}},		//Fragment Crossing, Mythril Stone
			{0x9a943b, {0x20, 0x2a6eebe}},		//Fragment Crossing, Mythril Crystal
			{0x9a943b, {0x40, 0x2a6eeca}},		//Fragment Crossing, AP Boost
			{0x9a943b, {0x80, 0x2a6eed6}},		//Fragment Crossing, Orichalcum
			{0x9a943d, {0x8, 0x2a6eee2}},		//Memory's Skyscraper, Mythril Crystal
			{0x9a944c, {0x1, 0x2a6eeee}},		//Memory's Skyscraper, AP Boost
			{0x9a944c, {0x2, 0x2a6eefa}},		//Memory's Skyscraper, Mythril Stone
			{0x9a943a, {0x20, 0x2a6ef06}},		//The Brink of Despair, Dark City Map
			{0x9a944a, {0x4, 0x2a6ef12}},		//The Brink of Despair, Orichalcum+
			{0x9a943c, {0x1, 0x2a6ef1e}},		//Nothing's Call, Mythril Gem
			{0x9a943c, {0x2, 0x2a6ef2a}},		//Nothing's Call, Orichalcum
			{0x9a943a, {0x40, 0x2a6ef36}},		//Twilight's View, Cosmic Belt
			{0x9a943c, {0x4, 0x2a6ef42}},		//Naught's Skyway, Mythril Gem
			{0x9a943c, {0x8, 0x2a6ef4e}},		//Naught's Skyway, Orichalcum
			{0x9a943c, {0x10, 0x2a6ef5a}},		//Naught's Skyway, Mythril Crystal
			{0x9a943c, {0x80, 0x2a6ef66}},		//Ruin and Creation's Passage, Mythril Stone
			{0x9a943d, {0x1, 0x2a6ef72}},		//Ruin and Creation's Passage, AP Boost
			{0x9a943d, {0x2, 0x2a6ef7e}}		//Ruin and Creation's Passage, Mythril Crystal
		}
	}
};