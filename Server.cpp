#include "Server.h"


std::vector<Server::CLIENT> clients;

void Server::start(int port)
{
	httplib::Server svr;
	svr.Get("/request", Server::on_request);

	svr.listen("0.0.0.0", port);
}

void Server::on_request(const httplib::Request& req, httplib::Response& res)
{
    CLIENT client = grab_client(req.remote_addr);
    if (client.ip.empty())
    {
        res.set_content("client not registered yet", "text/plain");
        return;
    }
    std::string s_response = Util::map_to_string(client.outstanding_checks);
    res.set_content(s_response, "text/plain");
}

Server::CLIENT Server::grab_client(std::string addr)
{
    for (CLIENT c : clients)
    {
        if (c.ip == addr)
        {
            return c;
        }
    }

    // client not registered yet
    CLIENT client;
    client.ip = addr;
    clients.push_back(client);
    return CLIENT();
}