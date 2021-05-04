#include "Util.h"

std::string Util::map_to_string(std::map<uint32_t, uint8_t>& checks)
{
    std::string result;
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

std::map<uint32_t, uint8_t> Util::string_to_map(std::string s)
{
    size_t current, previous = 0;
    std::string delimiter = "|";
    std::map<uint32_t, uint8_t> result;
    current = s.find(delimiter);
    while (current != std::string::npos)
    {
        std::string substr = s.substr(previous, current - previous);
        previous = current + 1;
        current = s.find(delimiter, previous);
        std::cout << substr << "\n\n";
    }
    std::cout << s.substr(previous, current - previous);
    return result;
}