#ifndef MICROMACHINES_CARSTATE_H
#define MICROMACHINES_CARSTATE_H

#include "Wheel.h"
#include <common/Coordinate.h>
#include <Box2D/Dynamics/b2Body.h>

#define RADTODEG 57.295779513082320876f

class CarState {

    public:
        virtual bool try_respawn(Coordinate respawn_point, b2Body* car_body, std::vector<Wheel*> wheels) = 0;

};


#endif //MICROMACHINES_CARSTATE_H
