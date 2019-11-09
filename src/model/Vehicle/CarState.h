#ifndef MICROMACHINES_CARSTATE_H
#define MICROMACHINES_CARSTATE_H

#include "Wheel.h"
#include "Box2D/Box2D.h"
#include "Box2D/Box2D.h"
#include <server/UpdateClient.h>

#define NOT_PRESSED 0

class CarState {

    public:
        virtual void move(int32_t movement, int32_t& throttle, int32_t& steering_wheel) = 0;

        virtual void stop(int32_t movement, int32_t& throttle, int32_t& steering_wheel) = 0;

};

#endif //MICROMACHINES_CARSTATE_H
