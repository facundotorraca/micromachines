#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "common/Socket.h"
#include "GameMode.h"
#include <string>

class Player {
    Socket socket;
    GameMode game_mode;
    std::string username;
    std::string match_name;

    public:
        Player(Socket&& socket, GameMode game_mode, std::string username, std::string match_name);

        Player(Player&& other) noexcept;

        void send(std::string& msg);

        bool is_on_join_mode();

        std::string get_match_name();

        std::string get_username();

        uint8_t receive_option();
};

#endif //MICROMACHINES_PLAYER_H
