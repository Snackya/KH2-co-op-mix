#include "Http_Client.hpp"

void Http_Client::send_checks(std::map<uint16_t, uint8_t>& checks)
{
	// for some reason keep_alive doesn't work only on sending,
	// so we need to recreate the client here
	delete cli;
	cli = new httplib::Client(server_address.c_str());
	std::string package = Utils::map_to_string(checks);
	std::cout << "package:\n" << package << std::endl;
	auto foo = cli->Post("/data", client_id, package, "text/plain");
}

std::map<uint16_t, uint8_t> Http_Client::request_checks()
{
	std::map<uint16_t, uint8_t> checks;
	auto res = cli->Get("/request", client_id);

	if (!res)
	{
		return checks;
	}

	std::string response = res->body.c_str();
	checks = Utils::string_to_map(response);

	return checks;
}

bool Http_Client::init(std::string server_addr, int port)
{
	server_address = server_addr + ":" + std::to_string(port);
	cli = new httplib::Client(server_address.c_str());
	cli->set_keep_alive(true);
	// get a client ID from the server
	auto res = cli->Get("/register");
	if (!res) return 0;
	std::string id = res->body.c_str();
	client_id = { {"ID", id} };
	return 1;
}