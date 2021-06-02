#pragma once
#include <cstdint>
#include <string>

static uint32_t WORLD = 0;
static uint32_t SAVE = 0;
static uint32_t SYS3 = 0;
static uint32_t BTL0 = 0;
static uint8_t GOA_WORLD_ID = 0x04;
static uint16_t GOA_WORLD_ROOM_ID = 0x1A04;

static void set_anchors(std::string mode)
{
    if (mode == "PC")
    {
        WORLD = 0x0714DB8;
        SAVE = 0x09A7070;
        SYS3 = 0x2A59DB0;
        BTL0 = 0x2A74840;
    }
    else if (mode == "PS2")
    {
        WORLD = 0x032BAE0;
        SAVE = 0x032BB30;
        SYS3 = 0x1CCB300;
        BTL0 = 0x1CE5D80;
    }
};