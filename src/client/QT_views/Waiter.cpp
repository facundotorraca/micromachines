//
// Created by alejoacevedo on 11/22/19.
//

#include <common/SocketError.h>
#include "Waiter.h"

Waiter::Waiter(ProtocolSocket &ps) : ps(ps) {}

void Waiter::wait_response() {
    try {
        uint8_t car = 1;
        this->ps.send(car);
        uint8_t flag_join_match = BAD_FLAG;
        this->ps.receive(flag_join_match);
        uint8_t flag_start_match = BAD_FLAG;
        this->ps.receive(flag_start_match);
        emit resultReady(flag_start_match);
    } catch(SocketError &error) {
        std::cout << "SOCKET ERROR" << std::endl;
        emit resultReady(CLOSE_CONNECTION);
    }

}