#include <vector>
#include "httplib.h"

class Server
{
private:
	inline static int id_counter = 0;

	struct CLIENT {
		std::string id;
		std::map<uint16_t, uint8_t>* outstanding_checks;
	};
	inline static std::vector<CLIENT> clients;

	static CLIENT grab_client(std::string addr);

	static void on_register(const httplib::Request& req, httplib::Response& res);
	static void on_data(const httplib::Request& req, httplib::Response& res, const httplib::ContentReader& content_reader);
	static void on_request(const httplib::Request&, httplib::Response& res);

public:

	static void start(int port);
};

