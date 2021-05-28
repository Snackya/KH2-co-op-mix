#include <string>
#include <map>
#include <vector>

// { form, { level, check address } }
std::map<std::string, std::map<uint8_t, uint32_t>> drive_checks = 
{
    {
        "Valor",
        {
            {0x02, 0x344AE},
            {0x03, 0x344B6},
            {0x04, 0x344BE},
            {0x05, 0x344C6},
            {0x06, 0x344CE},
            {0x07, 0x344D6},
        }
    },
    {
        "Wisdom",
        {
            {0x02, 0x344E6},
            {0x03, 0x344EE},
            {0x04, 0x344F6},
            {0x05, 0x344FE},
            {0x06, 0x34506},
            {0x07, 0x3450E},
        }
    },
    {
        "Limit",
        {
            {0x02, 0x3451E},
            {0x03, 0x34526},
            {0x04, 0x3452E},
            {0x05, 0x34536},
            {0x06, 0x3453E},
            {0x07, 0x34546},
        }
    },
    {
        "Master",
        {
            {0x02, 0x34556},
            {0x03, 0x3455E},
            {0x04, 0x34566},
            {0x05, 0x3456E},
            {0x06, 0x34576},
            {0x07, 0x3457E},
        }
    },
    {
        "Final",
        {
            {0x02, 0x3458E},
            {0x03, 0x34596},
            {0x04, 0x3459E},
            {0x05, 0x345A6},
            {0x06, 0x345AE},
            {0x07, 0x345B6},
        }
    },
    //{
    //    "Summon",
    //    {
    //        {0x02, 0x3446E},
    //        {0x03, 0x34476},
    //        {0x04, 0x3447E},
    //        {0x05, 0x34486},
    //        {0x06, 0x3448E},
    //        {0x07, 0x34496},
    //    }
    //},
};

// Save + addr anchor, have to add +2 offset for form level byte
std::map<uint16_t, std::string> drive_levels =
{
    {0x32F4, "Valor"},
    {0x332C, "Wisdom"},
    {0x3364, "Limit"},
    {0x339C, "Master"},
    {0x33D4, "Final"},
};