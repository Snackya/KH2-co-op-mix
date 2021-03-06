#include "Utils.hpp"

std::string Utils::map_to_string(std::map<uint16_t, uint8_t>& checks)
{
    std::string result = "";
    for (auto ch : checks)
    {
        result.append(std::to_string(ch.first));
        result.append(",");
        result.append(std::to_string(ch.second));
        result.append("|");
    }
    result = result.substr(0, result.size() - 1);
    return result;
}

std::map<uint16_t, uint8_t> Utils::string_to_map(std::string s)
{
    size_t current, previous = 0;
    std::string delimiter = "|";
    std::vector<std::string> pairs;
    std::map<uint16_t, uint8_t> result;
    current = s.find(delimiter);

    // k-v pairs split by '|'
    while (current != std::string::npos)
    {
        std::string substr = s.substr(previous, current - previous);
        previous = current + 1;
        current = s.find(delimiter, previous);
        pairs.push_back(substr);
    }
    pairs.push_back(s.substr(previous, current - previous));

    delimiter = ",";
    // k, v split by ','
    std::cout << std::endl;
    for (std::string pair : pairs)
    {
        size_t index = pair.find(delimiter);
        uint32_t key = std::strtoul((pair.substr(0, index)).c_str(), nullptr, 10);
        uint8_t val = std::strtoul((pair.substr(index+1, pair.size())).c_str(), nullptr, 10);
        result.emplace(key, val);
    }

    return result;
}

void Utils::print_byte(uint8_t byte)
{
    std::cout << "0x" << std::hex << (0xff & (unsigned int)byte) << std::endl;
}

std::vector<uint8_t> Utils::mask_to_values(uint8_t delta_val)
{
    std::vector<uint8_t> changed_bitmask_vals;
    for (int i = 0; i < 8; ++i)
    {
        if (delta_val >> i & 1)
        {
            changed_bitmask_vals.push_back(1 << i);
        }
    }
    return changed_bitmask_vals;
}

