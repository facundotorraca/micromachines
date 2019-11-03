#ifndef MICROMACHINES_RACECOMPLETED_H
#define MICROMACHINES_RACECOMPLETED_H

#include "RaceState.h"

class RaceCompleted : public RaceState {

    public:
        UpdateClient get_update(std::vector<Wheel*>& wheels, b2Body* car_body, int32_t ID) override {
            return UpdateClient({});
        }

};

#endif //MICROMACHINES_RACECOMPLETED_H
