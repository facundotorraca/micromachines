//
// Created by facundotorraca on 19/10/19.
//

#ifndef MICROMACHINES_UPDATECLIENT_H
#define MICROMACHINES_UPDATECLIENT_H

#include <common/ProtocolSocket.h>
#include <iostream>

class UpdateClient {
    std::vector<int32_t> message;

    public:
        UpdateClient(std::vector<int32_t>&& message);

        void send(ProtocolSocket &socket);
};

#endif //MICROMACHINES_UPDATECLIENT_H