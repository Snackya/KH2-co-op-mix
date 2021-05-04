#include <map>
#include <string>
#include <iostream>

class Util
{
private:

public:
	static std::string map_to_string(std::map<uint32_t, uint8_t>& checks);

	static std::map<uint32_t, uint8_t> string_to_map(std::string s);
};

