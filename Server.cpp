#include "Server.h"
#include "Util.h"

// TODO: general storage that gets sent out automatically when a new client connects
//       ensures a client can join midway without any problems.
//       everything except for drive levels and levels should be OR'able

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
    //std::cout << "data: \n" << body << std::endl;

    std::map<uint16_t, uint8_t> checks = Util::string_to_map(body.c_str());
    std::cout << "Received size: " << checks.size() << std::endl;

    CLIENT client = grab_client(source_id);
    for (auto check : checks)
    {
        // new key
        if (client.outstanding_checks->find(check.first) == client.outstanding_checks->end())
        {
            client.outstanding_checks->emplace(check.first, check.second);
        }
        else 
        {
            if (check.first == 0x000F || (check.first >= 0x32F4 && check.first <= 0x33D4))  // sora levels or drive levels
            {
                client.outstanding_checks->at(check.first) = std::max(client.outstanding_checks->at(check.first), check.second);
            }
            else    // merge bitmasks
            {
                client.outstanding_checks->at(check.first) = client.outstanding_checks->at(check.first) | check.second;
            }
        }
    }
    client.outstanding_checks->merge(checks);

    //for (CLIENT c : clients)
    //{
    //    if (c.id == source_id) continue;
    //    std::cout << "added the following map data to client #" << c.id << ":\n";
    //    std::map<uint16_t, uint8_t> checks = Util::string_to_map(body.c_str());
    //    for (auto check : checks)
    //    {
    //        std::cout << std::hex << check.first << " "; Util::print_byte(check.second);
    //    }
    //    std::cout << std::endl;
    //    // merge the new checks from the source client with the outstanding checks for each client
    //    c.outstanding_checks->merge(checks);
    //}
    res.set_content("ok", "text/plain");
}

// respond to client with new checks from other clients
void Server::on_request(const httplib::Request& req, httplib::Response& res)
{
    //std::cout << "all clients:" << std::endl;
    //for (CLIENT c : clients)
    //{
    //    std::cout << "id: " << c.id << std::endl;
    //    std::cout << "data: \n";
    //    for (auto foo : *(c.outstanding_checks))
    //    {
    //        std::cout << "0x" << std::hex << foo.first << " "; Util::print_byte(foo.second);
    //    }
    //    std::cout << std::endl;
    //}


    CLIENT client = grab_client(req.get_header_value("ID"));
    std::cout << "New request from client #" << client.id << std::endl;
    if (client.id.empty())
    {
        res.set_content("client not registered yet", "text/plain");
        return;
    }
    std::map<uint16_t, uint8_t> response_map;

    for (CLIENT c : clients)
    {
        if(c.id == client.id) continue;

        for(auto check : *(c.outstanding_checks))
        {
            // new key
            if (response_map.find(check.first) == response_map.end())
            {
                response_map.emplace(check.first, check.second);
            }
            else
            {
                if (check.first == 0x000F || (check.first >= 0x32F4 && check.first <= 0x33D4))  // sora levels or drive levels
                {
                    response_map.at(check.first) = std::max(response_map.at(check.first), check.second);
                }
                else    // merge bitmasks
                {
                    response_map.at(check.first) = response_map.at(check.first) | check.second;
                }
            }
        }
    }
    for (auto fak : response_map)
    {
        std::cout << std::hex << fak.first; Util::print_byte(fak.second);
    }
    std::string s_response = Util::map_to_string(response_map);
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