#include "Http_Client.h"

//void Http_Client::send_checks()
//{
//	// HTTP
//	httplib::Server svr;
//
//	svr.Get("/hi", [](const httplib::Request&, httplib::Response& res) {
//		res.set_content("Hello World!", "text/plain");
//		});
//
//	svr.listen("0.0.0.0", 8080);
//}

void Http_Client::send_checks(std::map<uint32_t, uint8_t>& checks)
{
	httplib::Params params;
	for (auto item : checks)
	{
		params.emplace(std::to_string(item.first), std::to_string(item.second));
	}
	for (auto stuff : params)
	{
		std::cout << stuff.first << " " << stuff.second << std::endl;
	}
}

std::map<uint32_t, uint8_t> Http_Client::request_checks()
{
	httplib::Client cli("http://127.0.0.1:49051");
	cli.set_keep_alive(true);
	std::map<uint32_t, uint8_t> mapp;
	auto res = cli.Get("/request");
	if (!res) return mapp;

	auto a = res->body;

	std::cout << res->body.c_str() << std::endl;
	
	return std::map<uint32_t, uint8_t>();
}
