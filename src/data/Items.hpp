#pragma once
#include <map>

// {ID, inventory address}
static inline std::map<uint16_t, uint16_t> items_id_invAddr =
{
    {0x0001, 0x3580},        // Potion
    {0x0002, 0x3581},        // Hi-Potion
    {0x0003, 0x3582},        // Ether
    {0x0004, 0x3583},        // Elixir
    {0x0005, 0x3584},        // Mega-Potion
    {0x0006, 0x3585},        // Mega-Ether
    {0x0007, 0x3586},        // Mega-Elixir
    {0x0008, 0x3587},        // Ability Ring
    {0x0009, 0x3588},        // Engineer Ring
    {0x000A, 0x3589},        // Technician Ring
    {0x000B, 0x358A},        // Expert Ring
    {0x000C, 0x358B},        // Sardonyx Ring
    {0x000D, 0x358C},        // Tourmaline Ring
    {0x000E, 0x358D},        // Aquamarine Ring
    {0x000F, 0x358E},        // Garnet Ring
    {0x0010, 0x358F},        // Diamond Ring
    {0x0011, 0x3590},        // Silver Ring
    {0x0012, 0x3591},        // Gold Ring
    {0x0013, 0x3592},        // Platinum Ring
    {0x0014, 0x3593},        // Mythril Ring
    {0x0020, 0x3598},        // Torn Page
    {0x001C, 0x359A},        // Orichalcum Ring
    {0x0022, 0x359B},        // Master Ring
    {0x0023, 0x359C},        // Moon Amulet
    {0x0024, 0x359E},        // Star Charm
    {0x0026, 0x359F},        // Skill Ring
    {0x0027, 0x35A0},        // Skillful Ring
    {0x0029, 0x35A1},        // Kingdom Key
    {0x002A, 0x35A2},        // Oathkeeper
    {0x002B, 0x35A3},        // Oblivion
    {0x002C, 0x35A4},        // Detection Saber
    {0x002D, 0x35A5},        // Frontier of Ultima
    {0x0028, 0x35A6},        // Soldier Earring
    {0x002E, 0x35A7},        // Fencer Earring
    {0x002F, 0x35A8},        // Mage Earring
    {0x0031, 0x35A9},        // Knight's Shield
    {0x0032, 0x35AA},        // Detection Shield
    {0x0033, 0x35AB},        // Test the King
    {0x0030, 0x35AC},        // Slayer Earring
    {0x0034, 0x35AD},        // Cosmic Ring
    {0x0036, 0x35AE},        // Battlefields of War (Auron's Weapon)
    {0x0037, 0x35AF},        // Sword of the Ancestors (Mulan's Weapon)
    {0x0035, 0x35B0},        // Medal
    {0x0038, 0x35B1},        // Cosmic Arts
    {0x0039, 0x35B2},        // Shadow Archive
    {0x003B, 0x35B3},        // Beast's Claw (Beast's Weapon)
    {0x003C, 0x35B4},        // Bone Fist (Jack's Weapon)
    {0x003D, 0x35B5},        // Proud Fang (Simba's Weapon)
    {0x003E, 0x35B6},        // Skill and Crossbones (Worse Jack's Weapon)
    {0x003A, 0x35B7},        // Shadow Archive+
    {0x003F, 0x35B8},        // Lucky Ring
    {0x0040, 0x35B9},        // Full Bloom
    {0x0041, 0x35BA},        // Draw Ring
    {0x0042, 0x35BB},        // Full Bloom+
    {0x0043, 0x35BC},        // Elven Bandana
    {0x0044, 0x35BD},        // Divine Bandana
    {0x0045, 0x35BE},        // Power Band
    {0x0048, 0x35C0},        // Scimitar (Aladdin's Weapon)
    {0x0049, 0x35C1},        // Way to the Dawn (Riku's Weapon)
    {0x004A, 0x35C2},        // Identity Disk (Tron's Weapon)
    {0x004B, 0x35C3},        // Mage's Staff
    //{0x----, 0x35C4},        // NULL (used as flag for Ollete's Munny Pouch)
    //{0x----, 0x35C5},        // NULL (used as flag for Mickey's Munny Pouch in Lua)
    {0x0046, 0x35C6},        // Buster Band
    {0x004E, 0x35C7},        // Protect Belt
    //{0x----, 0x35C8},        // >ID Not Found< (Partner Weapon, Not the Keyblade)
    //{0x----, 0x35C9},        // >ID Not Found< (Keyblade)
    {0x004F, 0x35CA},        // Gaia Belt
    //{0x----, 0x35CB},        // NULL (used as flag for Mickey's Munny Pouch in Pnach)
    {0x006F, 0x35D1},        // Cosmic Belt
    {0x0084, 0x35D2},        // Shock Charm
    {0x0085, 0x35D3},        // Shock Charm+
    {0x009D, 0x35D4},        // Grand Ribbon
    {0x00AD, 0x35D7},        // Fire Bangle
    {0x00AE, 0x35D8},        // Fira Bangle
    {0x00C5, 0x35D9},        // Firaga Bangle
    {0x011C, 0x35DA},        // Firagun Bangle
    {0x011E, 0x35DC},        // Blizzard Armlet
    {0x011F, 0x35DD},        // Blizzara Armlet
    {0x0120, 0x35DE},        // Blizzaga Armlet
    {0x0121, 0x35DF},        // Blizzagun Armlet
    {0x0083, 0x35E1},        // Tent
    {0x0123, 0x35E2},        // Thunder Trinket
    {0x0124, 0x35E3},        // Thundara Trinket
    {0x0125, 0x35E4},        // Thundaga Trinket
    {0x0126, 0x35E5},        // Thundagun Trinket
    {0x008B, 0x35E6},        // Adamant Shield
    {0x008C, 0x35E7},        // Chain Gear
    {0x008D, 0x35E8},        // Ogre Shield
    {0x008E, 0x35E9},        // Falling Star
    {0x008F, 0x35EA},        // Dreamcloud
    {0x0090, 0x35EB},        // Knight Defender
    {0x0091, 0x35EC},        // Genji Shield
    {0x0092, 0x35ED},        // Akashic Record
    {0x0093, 0x35EE},        // Nobody Guard
    {0x0094, 0x35EF},        // Hammer Staff
    {0x0095, 0x35F0},        // Victory Bell
    {0x0096, 0x35F1},        // Meteor Staff
    {0x0097, 0x35F2},        // Comet Staff
    {0x0098, 0x35F3},        // Lord's Broom
    {0x0099, 0x35F4},        // Wisdom Wand
    {0x009A, 0x35F5},        // Rising Dragon
    {0x009B, 0x35F6},        // Nobody Lance
    {0x009C, 0x35F7},        // Shaman's Relic
    {0x0128, 0x35F9},        // Shadow Anklet
    {0x00A1, 0x35FA},        // Staff of Detection
    {0x0129, 0x35FB},        // Dark Anklet
    {0x012A, 0x35FC},        // Midnight Anklet
    {0x012B, 0x35FD},        // Chaos Anklet
    {0x012D, 0x35FF},        // Abas Chain
    {0x012E, 0x3600},        // Aegis Chain
    {0x012F, 0x3601},        // Acrisius
    {0x0130, 0x3602},        // Ribbon
    {0x0131, 0x3603},        // Champion Belt
    {0x0132, 0x3604},        // Petite Ribbon
    {0x0133, 0x3605},        // Acrisius+
    {0x0134, 0x3606},        // Cosmic Chain
    {0x013D, 0x360F},        // Blazing Shard
    {0x013E, 0x3610},        // Blazing Stone
    {0x013F, 0x3611},        // Blazing Gem
    {0x0140, 0x3612},        // Blazing Crystal
    {0x0145, 0x3617},        // Lightning Shard
    {0x0146, 0x3618},        // Lightning Stone
    {0x0147, 0x3619},        // Lightning Gem
    {0x0148, 0x361A},        // Lightning Crystal
    {0x0149, 0x361B},        // Power Shard
    {0x014A, 0x361C},        // Power Stone
    {0x014B, 0x361D},        // Power Gem
    {0x014C, 0x361E},        // Power Crystal
    {0x014D, 0x361F},        // Lucid Shard
    {0x014E, 0x3620},        // Lucid Stone
    {0x014F, 0x3621},        // Lucid Gem
    {0x0150, 0x3622},        // Lucid Crystal
    {0x0151, 0x3623},        // Dense Shard
    {0x0152, 0x3624},        // Dense Stone
    {0x0153, 0x3625},        // Dense Gem
    {0x0154, 0x3626},        // Dense Crystal
    {0x0155, 0x3627},        // Twilight Shard
    {0x0156, 0x3628},        // Twilight Stone
    {0x0157, 0x3629},        // Twilight Gem
    {0x0158, 0x362A},        // Twilight Crystal
    {0x0159, 0x362B},        // Mythril Shard
    {0x015A, 0x362C},        // Mythril Stone
    {0x015B, 0x362D},        // Mythril Gem
    {0x015C, 0x362E},        // Mythril Crystal
    {0x015D, 0x362F},        // Bright Shard
    {0x015E, 0x3630},        // Bright Stone
    {0x015F, 0x3631},        // Bright Gem
    {0x0160, 0x3632},        // Bright Crystal
    {0x0161, 0x3633},        // Energy Shard
    {0x0162, 0x3634},        // Energy Stone
    {0x0163, 0x3635},        // Energy Gem
    {0x0164, 0x3636},        // Energy Crystal
    {0x0165, 0x3637},        // Serenity Shard
    {0x0166, 0x3638},        // Serenity Stone
    {0x0167, 0x3639},        // Serenity Gem
    {0x0168, 0x363A},        // Serenity Crystal
    {0x0169, 0x363B},        // Orichalcum+
    {0x0217, 0x363C},        // Munny Pouch (Olette)
    {0x016B, 0x363D},        // Crystal Orb
    {0x016C, 0x363E},        // Seifer's Trophy
    {0x016D, 0x363F},        // Tournament Poster
    {0x016E, 0x3640},        // Poster
    {0x016F, 0x3641},        // Letter
    {0x0170, 0x3642},        // Namine's Sketches
    {0x0171, 0x3643},        // Membership Card
    {0x0172, 0x3644},        // Olympus Stone
    {0x0173, 0x3645},        // Auron's Statue
    {0x0174, 0x3646},        // Cursed Medallion
    {0x0175, 0x3647},        // Present
    {0x0176, 0x3648},        // Decoy Presents
    {0x0177, 0x3649},        // Ice Cream
    {0x0178, 0x364A},        // Picture
    {0x0179, 0x364B},        // Orichalcum
    {0x017A, 0x364C},        // Frost Shard
    {0x017B, 0x364D},        // Frost Stone
    {0x017C, 0x364E},        // Frost Gem
    {0x017D, 0x364F},        // Frost Crystal
    {0x017E, 0x3650},        // Mega-Recipe
    {0x0180, 0x3651},        // Struggle Sword
    {0x01C1, 0x3652},        // Star Recipe
    {0x01C2, 0x3653},        // Recovery Recipe
    {0x01C3, 0x3654},        // Skill Recipe
    {0x01C4, 0x3655},        // Guard Recipe
    //{0x----, 0x3656},        // >Dummy 06<
    //{0x----, 0x3657},        // >Dummy 07<
    //{0x----, 0x3658},        // >Dummy 08<
    //{0x----, 0x3659},        // >Dummy 09<
    //{0x----, 0x365A},        // >Dummy 10<
    //{0x----, 0x365B},        // >Dummy 11<
    //{0x----, 0x368C},        // >Dummy 12<
    //{0x----, 0x365D},        // >Dummy 13<
    //{0x----, 0x365E},        // >Dummy 14<
    //{0x----, 0x365F},        // >Dummy 15<
    //{0x----, 0x3660},        // >Dummy 16< (Gained Item Slot!)
    {0x01D0, 0x3661},        // Road to Discovery
    {0x01D1, 0x3662},        // Strength Beyond Strength
    {0x01D2, 0x3663},        // Book of Shadows
    {0x0112, 0x3664},        // Drive Recovery
    {0x0113, 0x3665},        // High Drive Recovery
    {0x0114, 0x3666},        // Power Boost
    {0x0115, 0x3667},        // Magic Boost
    {0x0116, 0x3668},        // Defense Boost
    {0x0117, 0x3669},        // AP Boost
    {0x0118, 0x366A},        // Dark Shard
    {0x0119, 0x366B},        // Dark Stone
    {0x011A, 0x366C},        // Dark Gem
    {0x011B, 0x366D},        // Dark Crystal
    {0x01D3, 0x366E},        // Cloaked Thunder
    {0x01D4, 0x366F},        // Eternal Blossom
    {0x01D5, 0x3670},        // Rare Document
    //{0x----, 0x3671},        // >Dummy 23< (Maximum HP Increased!)
    //{0x----, 0x3672},        // >Dummy 24< (Maximum MP Increased!)
    //{0x----, 0x3673},        // >Dummy 25< (Drive Gauge Powered Up!)
    //{0x----, 0x3674},        // >Dummy 26< (Gained Armor Slot!)
    //{0x----, 0x3675},        // >Dummy 27< (Gained Accessory Slot!)
    {0x01DB, 0x3676},        // Style Recipe
    {0x01DC, 0x3677},        // Moon Recipe
    {0x01DD, 0x3678},        // Queen Recipe
    {0x01DE, 0x3679},        // King Recipe
    {0x01DF, 0x367A},        // Ultimate Recipe
    {0x01E0, 0x367B},        // Star Seeker
    {0x01E1, 0x367C},        // Hidden Dragon
    {0x01E2, 0x367D},        // Save the Queen
    {0x01E3, 0x367E},        // Save the King
    {0x01E4, 0x367F},        // Hero's Crest
    {0x01E5, 0x3680},        // Monochrome
    {0x01E6, 0x3681},        // Follow the Wind
    {0x01E7, 0x3682},        // Circle of Life
    {0x01E8, 0x3683},        // Photon Debugger
    {0x01E9, 0x3684},        // Gull Wing
    {0x01EA, 0x3685},        // Rumbling Rose
    {0x01EB, 0x3686},        // Guardian Soul
    {0x01EC, 0x3687},        // Wishing Lamp
    {0x01ED, 0x3688},        // Decisive Pumpkin
    {0x01EE, 0x3689},        // Sleeping Lion
    {0x01EF, 0x368A},        // Sweet Memories
    {0x01F0, 0x368B},        // Mysterious Abyss
    {0x01F1, 0x368C},        // Fatal Crest
    {0x01F2, 0x368D},        // Bond of Flame
    {0x01F3, 0x368E},        // Fenrir
    {0x01F4, 0x368F},        // Ultima Weapon
    {0x01F5, 0x3690},        // Struggle Wand
    {0x01F6, 0x3691},        // Struggle Hammer
    {0x01F7, 0x3692},        // Save the Queen+
    {0x01F8, 0x3693},        // Save the King+
    {0x020C, 0x3694},        // Promise Charm
    {0x0217, 0x3695},        // Munny Pouch (Mickey)
    {0x0219, 0x3696},        // Hades Cup Trophy
    {0x021A, 0x3697},        // "The Struggle" Trophy
    {0x021F, 0x3698},        // Two Become One
    {0x0220, 0x3699},        // Winner's Proof
    {0x0221, 0x369A},        // Centurion
    {0x0222, 0x369B},        // Centurion+
    {0x0223, 0x369C},        // Plain Mushroom
    {0x0224, 0x369D},        // Plain Mushroom+
    {0x0225, 0x369E},        // Precious Mushroom
    {0x0226, 0x369F},        // Precious Mushroom+
    {0x0227, 0x36A0},        // Premium Mushroom
    {0x0228, 0x36A1},        // Frozen Pride
    {0x0229, 0x36A2},        // Frozen Pride+
    {0x022A, 0x36A3},        // Joyous Mushroom
    {0x022B, 0x36A4},        // Joyous Mushroom+
    {0x022C, 0x36A5},        // Majestic Mushroom
    {0x022D, 0x36A6},        // Majestic Mushroom+
    {0x022E, 0x36A7},        // Ultimate Mushroom
    {0x0240, 0x36A8},        // Remembrance Shard
    {0x0241, 0x36A9},        // Remembrance Stone
    {0x0242, 0x36AA},        // Remembrance Gem
    {0x0243, 0x36AB},        // Remembrance Crystal
    {0x0244, 0x36AC},        // Tranquility Shard
    {0x0245, 0x36AD},        // Tranquility Stone
    {0x0246, 0x36AE},        // Tranquility Gem
    {0x0247, 0x36AF},        // Tranquility Crystal
    {0x0248, 0x36B0},        // Lost Illusion
    {0x0249, 0x36B1},        // Manifest Illusion
    {0x0251, 0x36B2},        // Proof of Connection
    {0x0252, 0x36B3},        // Proof of Nonexistence
    {0x0253, 0x36B4},        // Proof of Peace
    {0x0257, 0x36B5},        // Executive's Ring
    {0x0258, 0x36B6},        // Shaman's Relic+
    {0x0259, 0x36B7},        // Akashic Record+
};

// {ID, {bitmask address, bitmask value} }
static inline std::map<uint16_t, std::pair<uint16_t, uint8_t>> items_invBitmask =
{
    {0x0019, {0x36C0, 0x01}},        // Ukulele Charm
    {0x001A, {0x36C0, 0x02}},        // Valor Form
    {0x001B, {0x36C0, 0x04}},        // Wisdom Form
    {0x017F, {0x36C0, 0x08}},        // Baseball Charm
    {0x001D, {0x36C0, 0x10}},        // Final Form
    {0x001E, {0x36C0, 0x20}},        // Anti Form
    {0x001F, {0x36C0, 0x40}},        // Master Form
    {0x0059, {0x36C0, 0x80}},        // Navigational Map
    {0x005A, {0x36C1, 0x01}},        // Castle Map
    {0x005B, {0x36C1, 0x02}},        // Basement Map
    {0x005C, {0x36C1, 0x04}},        // Castle Walls Map
    {0x01F9, {0x36C1, 0x20}},        // The Interceptor Map
    {0x0070, {0x36C1, 0x40}},        // Encampment Area Map
    {0x0071, {0x36C1, 0x80}},        // Village Area Map
    {0x0072, {0x36C2, 0x01}},        // Cornerstone Hill Map
    {0x0073, {0x36C2, 0x02}},        // Windows of Time Map 2
    {0x0074, {0x36C2, 0x04}},        // Lilliput Map
    {0x0075, {0x36C2, 0x08}},        // Building Site Map
    {0x0076, {0x36C2, 0x10}},        // Mickey's House Map
    {0x0077, {0x36C2, 0x20}},        // Disney Castle Map
    {0x0078, {0x36C2, 0x40}},        // Agrabah Map
    {0x0079, {0x36C2, 0x80}},        // Cave of Wonders Map
    {0x007A, {0x36C3, 0x01}},        // Ruins Map
    {0x007B, {0x36C3, 0x02}},        // Undersea Kingdom Map
    {0x007C, {0x36C3, 0x04}},        // Starry Hill Map
    {0x007D, {0x36C3, 0x08}},        // 100 Acre Wood Map
    {0x007E, {0x36C3, 0x10}},        // Rabbit's Howse Map
    {0x007F, {0x36C3, 0x20}},        // Piglet's Howse Map
    {0x0080, {0x36C3, 0x40}},        // Kanga's Howse Map
    {0x0081, {0x36C4, 0x80}},        // Spooky Cave Map
    {0x0082, {0x36C4, 0x01}},        // Palace Map
    {0x0086, {0x36C4, 0x02}},        // Coliseum Map
    {0x0087, {0x36C4, 0x04}},        // Underworld Map
    {0x0088, {0x36C4, 0x08}},        // Caverns Map
    {0x009F, {0x36C4, 0x10}},        // Lamp Charm
    {0x00A0, {0x36C4, 0x20}},        // Feather Charm
    {0x00E2, {0x36C4, 0x40}},        // Report 1
    {0x00E3, {0x36C4, 0x80}},        // Report 2
    {0x00E4, {0x36C5, 0x01}},        // Report 3
    {0x00E5, {0x36C5, 0x02}},        // Report 4
    {0x00E6, {0x36C5, 0x04}},        // Report 5
    {0x00E7, {0x36C5, 0x08}},        // Report 6
    {0x00E8, {0x36C5, 0x10}},        // Report 7
    {0x00E9, {0x36C5, 0x20}},        // Report 8
    {0x00EA, {0x36C5, 0x40}},        // Report 9
    {0x00EB, {0x36C5, 0x80}},        // Report 10
    {0x00EC, {0x36C6, 0x01}},        // Report 11
    {0x00ED, {0x36C6, 0x02}},        // Report 12
    {0x00EE, {0x36C6, 0x04}},        // Report 13
    {0x00FA, {0x36C7, 0x04}},        // Halloween Town Map
    {0x00FB, {0x36C7, 0x08}},        // Naval Map
    {0x00FC, {0x36C7, 0x10}},        // Pride Rock Map
    {0x00FD, {0x36C7, 0x20}},        // Marketplace Map
    {0x00FE, {0x36C7, 0x40}},        // Pit Cell Area Map
    {0x00FF, {0x36C7, 0x80}},        // Twilight Town Map
    {0x0100, {0x36C8, 0x01}},        // Dark City Map
    {0x01FA, {0x36C8, 0x02}},        // The Black Pearl Map
    {0x01FB, {0x36C8, 0x04}},        // Isla de Muerta Map
    {0x01FC, {0x36C8, 0x08}},        // Ship Graveyard Map
    {0x01FD, {0x36C8, 0x10}},        // Christmas Town Map
    {0x01FE, {0x36C8, 0x20}},        // Curly Hill Map
    {0x01FF, {0x36C8, 0x40}},        // Oasis Map
    {0x0200, {0x36C8, 0x80}},        // Savannah Map
    {0x0201, {0x36C9, 0x01}},        // Castle Perimeter Map
    {0x0202, {0x36C9, 0x02}},        // The Great Maw Map
    {0x0203, {0x36C9, 0x04}},        // I/O Tower Map
    {0x0204, {0x36C9, 0x08}},        // Central Computer Core Map
    {0x0205, {0x36C9, 0x10}},        // Solar Sailer Simulation Map
    {0x0206, {0x36C9, 0x20}},        // Windows of Time Map
    {0x0213, {0x36C9, 0x40}},        // Sunset Hill Map
    {0x0214, {0x36C9, 0x80}},        // Mansion Map
    {0x0215, {0x36CA, 0x01}},        // Tower Map
    {0x0216, {0x36CA, 0x02}},        // DH Map
    {0x0218, {0x36CA, 0x04}},        // Castle that Never Was Map
    {0x0233, {0x36CA, 0x08}},        // Limit Form
    {0x024A, {0x36CA, 0x10}},        // Dark Remembrance Map
    {0x024E, {0x36CA, 0x20}},        // Depths of Remembrance Map
    {0x0250, {0x36CA, 0x80}},        // Garden of Assemblage Map
};
