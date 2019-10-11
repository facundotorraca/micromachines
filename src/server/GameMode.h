#ifndef MICROMACHINES_GAMEMODE_H
#define MICROMACHINES_GAMEMODE_H

#include <cstdint>
#include <string>

class GameMode {
    uint8_t mode;
    std::string match_name;

    public:
        GameMode(uint8_t mode, std::string match_name);

        bool is_join();

        std::string get_match_name();
};


#endif //MICROMACHINES_GAMEMODE_H
