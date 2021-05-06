#include "Http_Client.h"
#include "Util.h"

void Http_Client::send_checks(std::map<uint32_t, uint8_t>& checks)
{
	cli->Post("/data", client_id, Util::map_to_string(checks), "text/plain");
}

std::map<uint32_t, uint8_t> Http_Client::request_checks()
{
	std::map<uint32_t, uint8_t> checks;
	auto res = cli->Get("/request", client_id);
	if (!res) return checks;

	std::string response = res->body.c_str();

	checks = Util::string_to_map(response);
	return checks;
}

void Http_Client::init(std::string server_addr)
{
	cli = new httplib::Client(server_addr.c_str());
	cli->set_keep_alive(true);

	// get a client ID from the server
	auto res = cli->Get("/register");
	if (!res) return;
	std::string id = res->body.c_str();
	client_id = { {"ID", id} };
}