//
// Created by alejoacevedo on 11/22/19.
//

#include "Waiter.h"

#define BAD_FLAG 1

Waiter::Waiter(ProtocolSocket &ps) : ps(ps) {}

void Waiter::wait_response() {
    uint8_t car = 1;
    this->ps.send(car);
    uint8_t flag_join_match = BAD_FLAG;
    this->ps.receive(flag_join_match);
    uint8_t flag_start_match = BAD_FLAG;
    this->ps.receive(flag_start_match);
    emit resultReady(flag_start_match);
}