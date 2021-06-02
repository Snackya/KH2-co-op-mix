#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>

class Utils
{
private:

public:
	static std::string map_to_string(std::map<uint16_t, uint8_t>& checks);
	static std::map<uint16_t, uint8_t> string_to_map(std::string s);

	static std::vector<uint8_t> mask_to_values(uint8_t delta_val);
	static void print_byte(uint8_t byte);
};

