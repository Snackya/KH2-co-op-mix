#include "httplib.h"
#include "Util.h"

class Server
{
private:



public:
	struct CLIENT {
		std::string ip;
		std::map<uint32_t, uint8_t> outstanding_checks;
	};
	static CLIENT grab_client(std::string addr);

	static void start(int port);


	static void on_request(const httplib::Request&, httplib::Response& res);
};

