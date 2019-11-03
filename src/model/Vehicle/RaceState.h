#ifndef MICROMACHINES_RACESTATE_H
#define MICROMACHINES_RACESTATE_H

#include "Wheel.h"
#include "Box2D/Box2D.h"
#include <server/UpdateClient.h>

class RaceState {

    public:
        virtual UpdateClient get_update(std::vector<Wheel*>& wheels, b2Body* body, int32_t ID) = 0;

};

#endif //MICROMACHINES_RACESTATE_H
