#include "httplib.h"
#include <map>

class Http_Client
{
private:
	inline static httplib::Client* cli;
	inline static httplib::Headers client_id;
	inline static std::string server_addresss;

public:
	static void send_checks(std::map<uint32_t, uint8_t>& checks);

	static std::map<uint32_t, uint8_t> request_checks();

	static void init(std::string server_addr);
};

