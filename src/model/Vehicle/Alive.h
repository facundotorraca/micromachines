#ifndef MICROMACHINES_ALIVE_H
#define MICROMACHINES_ALIVE_H

#include "CarState.h"

class Alive : public CarState {

    public:
        bool try_respawn(Coordinate respawn_point, b2Body* car_body, std::vector<Wheel*> wheels) override {
            return false;
        }

};


#endif //MICROMACHINES_ALIVE_H
