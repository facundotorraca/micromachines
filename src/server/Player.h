#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include <string>
#include "common/Socket.h"
#include <common/ProtocolSocket.h>

class Player {
    ProtocolSocket p_socket;
    uint8_t mode;
    std::string username;
    std::string match_name;

    public:
        Player(ProtocolSocket&& p_socket, uint8_t mode, std::string username, std::string match_name);

        bool is_called(std::string& username);

        Player(Player&& other) noexcept;

        std::string get_match_name();

        void send(std::string& msg);

        std::string get_username();

        uint8_t receive_option();

        bool is_on_join_mode();

        void kill();
};

#endif //MICROMACHINES_PLAYER_H
