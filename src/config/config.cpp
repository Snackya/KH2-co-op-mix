#include "config.hpp"

bool Config::set_config(std::string filename)
{
    std::ifstream con_file(filename);
    if (con_file.is_open())
    {
        std::string line;
        while (getline(con_file, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            if (name == "HOST_ADDRESS")
            {
                SERVER_ADDR = value;
                if (value == "127.0.0.1") Config::HOSTING = true;
            }
            else if (name == "PORT") PORT = stoi(value);
            else if (name == "VERSION") GAME_VERSION = value;
            else if (name == "SHARE_LEVELS") SHARE_LEVELS = stoi(value);
            else if (name == "SHARE_DRIVES") SHARE_DRIVES = stoi(value);
            else if (name == "SHARE_PROGRESS") SHARE_PROGRESS = stoi(value);
        }
        return 1;
    }
    else
    {
        std::cout << "config.txt not found." << std::endl;
        return 0;
    }
}