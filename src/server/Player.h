#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "common/Socket.h"
#include "GameMode.h"
#include <string>

class Player {
    std::string username;
    Socket socket;
    GameMode game_mode;

    public:
        Player(Socket&& socket, GameMode game_mode, std::string username);

        Player(Player&& other);

        void send(std::string msg);

        bool is_on_join_mode();

        std::string get_match_name();

        std::string get_username();

        uint8_t receive_option();
};

#endif //MICROMACHINES_PLAYER_H
