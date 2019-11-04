#ifndef MICROMACHINES_CARSTATE_H
#define MICROMACHINES_CARSTATE_H

#include "Wheel.h"
#include "Box2D/Box2D.h"
#include <server/UpdateClient.h>

#define NOT_PRESSED 0

class CarState {

    public:
        virtual void move(int32_t key, int32_t& key_v, int32_t& key_h) = 0;

        virtual void stop(int32_t key, int32_t& key_v, int32_t& key_h) = 0;

};

#endif //MICROMACHINES_CARSTATE_H
