//
// Created by facundotorraca on 19/10/19.
//

#ifndef MICROMACHINES_UPDATERACE_H
#define MICROMACHINES_UPDATERACE_H

#include <vector>
#include <map>
#include "model/Car.h"

class UpdateRace {
    int32_t client_ID;
    uint8_t key_state;
    uint8_t key;

public:
    UpdateRace( int32_t client_ID, uint8_t key, uint8_t key_state);

    void update_cars(std::map<uint8_t, Car>& cars);

};


#endif //MICROMACHINES_UPDATERACE_H
