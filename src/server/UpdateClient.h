#ifndef MICROMACHINES_UPDATECLIENT_H
#define MICROMACHINES_UPDATECLIENT_H

#include <iostream>
#include <common/ProtocolSocket.h>

class UpdateClient {

    std::string string_message;
    std::vector<int32_t> message;

    public:
        explicit UpdateClient(std::vector<int32_t>&& message);

        explicit UpdateClient(std::string string_message);

        void send(ProtocolSocket &socket);
};

#endif //MICROMACHINES_UPDATECLIENT_H