#include "Http_Client.hpp"
#include "../util/Utils.hpp"

void Http_Client::send_checks(std::map<uint16_t, uint8_t>& checks)
{
	// for some reason keep_alive doesn't work only on sending,
	// so we need to recreate the client here
	delete cli;
	cli = new httplib::Client(server_addresss.c_str());
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

void Http_Client::init(std::string server_addr)
{
	server_addresss = server_addr;
	cli = new httplib::Client(server_addresss.c_str());
	cli->set_keep_alive(true);
	// get a client ID from the server
	auto res = cli->Get("/register");
	if (!res) return;
	std::string id = res->body.c_str();
	std::cout << "received id " << id << " from server" << std::endl;
	client_id = { {"ID", id} };
}