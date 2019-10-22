#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include <string>
#include "common/Socket.h"
#include "UpdateRace.h"
#include "UpdateClient.h"
#include <common/ProtocolSocket.h>

class Player {
    ProtocolSocket p_socket;
    uint8_t mode;

    int32_t ID;
    int32_t car_model; /* esto despues se puede cambiar*/
    std::string username;
    std::string match_name;

    public:
        Player(ProtocolSocket&& p_socket, uint8_t mode, std::string username, std::string match_name);

        bool is_called(std::string& username);

        Player(Player&& other) noexcept;

        void set_car_model(uint8_t car_model);

        std::string get_match_name();

        void send(std::vector<int32_t>& msg);

        void send(std::string& msg);

        void send(UpdateClient update);

        std::string get_username();

        uint8_t receive_option();

        UpdateRace receive_update();

        bool is_on_join_mode();

    void kill();
};

#endif //MICROMACHINES_PLAYER_H
