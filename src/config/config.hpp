#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Config {
private:

public:
    // defaults
    static inline std::string GAME_VERSION = "PC";

    static inline std::string SERVER_ADDR = "127.0.0.1";
    static inline int PORT = 7356;
    static inline bool HOSTING = false;

    static inline bool SHARE_LEVELS = true;
    static inline bool SHARE_DRIVES = true;
    static inline bool SHARE_PROGRESS = false;

    static bool set_config(std::string filename);
};