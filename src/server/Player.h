#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "common/Socket.h"
#include "GameMode.h"

class Player {
    Socket socket;
    GameMode game_mode;

    public:
        Player(Socket&& socket, GameMode game_mode);

        Player(Player&& other);

        void send(std::string msg);

        bool is_on_join_mode();

    std::string get_match_name();
};


#endif //MICROMACHINES_PLAYER_H
