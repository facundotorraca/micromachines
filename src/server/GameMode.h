#ifndef MICROMACHINES_GAMEMODE_H
#define MICROMACHINES_GAMEMODE_H

#include <cstdint>
#include <string>

class GameMode {
    uint8_t mode;

    public:
        explicit GameMode(uint8_t mode);

        bool is_join();
};


#endif //MICROMACHINES_GAMEMODE_H
