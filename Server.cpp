#include "Server.h"
#include "Util.h"

void Server::start(int port)
{
	httplib::Server svr;

	svr.Get("/request", Server::on_request);
    svr.Get("/register", Server::on_register);
    svr.Post("/data", Server::on_data);

	svr.listen("0.0.0.0", port);
}

// register client with id
void Server::on_register(const httplib::Request& req, httplib::Response& res)
{
    //CLIENT client{ std::to_string(Server::id_counter), std::map<uint32_t, uint8_t>() };
    CLIENT client;
    client.id = std::to_string(Server::id_counter);
    client.outstanding_checks = new std::map<uint16_t, uint8_t>;
    std::cout << "Registered client #" << Server::id_counter << std::endl;
    clients.push_back(client);
    res.set_content(std::to_string(Server::id_counter), "text/plain");
    Server::id_counter++;
}

// receive new checks from client
void Server::on_data(const httplib::Request& req, httplib::Response& res, const httplib::ContentReader& content_reader)
{
    std::string source_id = req.get_header_value("ID");
    std::string body = "";
     //idk wtf this library is even doing at this point. dumb shit at least.
    content_reader([&](const char* data, size_t data_length) {
        body.append(data, data_length);
        return true;
        });
    std::cout << "Data received from client #" << source_id << std::endl;
    std::cout << "data: \n" << body << std::endl;
    for (CLIENT c : clients)
    {
        if (c.id == source_id) continue;
        std::cout << "added the following map data to client #" << c.id << ":\n";
        std::map<uint16_t, uint8_t> checks = Util::string_to_map(body.c_str());
        for (auto check : checks)
        {
            std::cout << check.first << " " << check.second << std::endl;
        }
        std::cout << std::endl;
        // merge the new checks from the source client with the outstanding checks for each client
        c.outstanding_checks->merge(checks);
    }
    res.set_content("ok", "text/plain");
}

// respond to client with new checks from other clients
void Server::on_request(const httplib::Request& req, httplib::Response& res)
{
    std::cout << "all clients:" << std::endl;
    for (CLIENT c : clients)
    {
        std::cout << "id: " << c.id << std::endl;
        std::cout << "data: \n";
        for (auto foo : *(c.outstanding_checks))
        {
            std::cout << foo.first << " " << foo.second << "\n";
        }
        std::cout << std::endl;
    }


    CLIENT client = grab_client(req.get_header_value("ID"));
    std::cout << "New request from client #" << client.id << std::endl;
    if (client.id.empty())
    {
        res.set_content("client not registered yet", "text/plain");
        return;
    }
    std::cout << "Outstanding checks are:" << std::endl;
    for (auto check : *(client.outstanding_checks))
    {
        std::cout << check.first << " " << check.second << std::endl;
    }
    std::string s_response = Util::map_to_string(*(client.outstanding_checks));
    std::cout << "Responding with:\n" << s_response.c_str() << std::endl;
    res.set_content(s_response.c_str(), "text/plain");
}

Server::CLIENT Server::grab_client(std::string id)
{
    for (CLIENT c : clients)
    {
        if (c.id == id)
        {
            return c;
        }
    }
    // not registered
    return CLIENT();
}