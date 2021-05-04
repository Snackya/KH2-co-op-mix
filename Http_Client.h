#include "httplib.h"
#include <map>

class Http_Client
{
private:

public:
	static void send_checks(std::map<uint32_t, uint8_t>& checks);

	static std::map<uint32_t, uint8_t> request_checks();
};

