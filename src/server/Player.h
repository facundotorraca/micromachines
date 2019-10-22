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
    int32_t car_model;                                                  /* esto despues se puede cambiar*/
    std::string username;
    std::string match_name;

    public:
        Player(ProtocolSocket&& p_socket, uint8_t mode, std::string username, std::string match_name);

        Player(Player&& other) noexcept;

        bool is_called(std::string& username);

        void set_car_model(uint8_t car_model);

        void send(std::vector<int32_t>& msg);

        void send(UpdateClient update);

        void send(std::string& msg);

        std::string get_match_name();

        UpdateRace receive_update();

        std::string get_username();

        uint8_t receive_option();

        void set_ID(int32_t id);

        bool is_on_join_mode();

        void kill();
};

#endif //MICROMACHINES_PLAYER_H
