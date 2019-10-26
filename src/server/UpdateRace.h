#ifndef MICROMACHINES_UPDATERACE_H
#define MICROMACHINES_UPDATERACE_H

#include <map>
#include <vector>
#include <unordered_map>
#include "model/Vehicle/Car.h"

class UpdateRace {
    int32_t key;
    int32_t key_state;
    int32_t client_ID;

public:
    UpdateRace(int32_t client_ID, int32_t key, int32_t key_state);

    void update_cars(std::unordered_map<int32_t, Car>& cars);
};


#endif //MICROMACHINES_UPDATERACE_H
