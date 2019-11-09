#ifndef MICROMACHINES_CARON_H
#define MICROMACHINES_CARON_H

#include "CarState.h"
#include <common/EntityType.h>

#define RADTODEG 57.295779513082320876f

class CarOn : public CarState {

    public:
         void move(int32_t movement, int32_t& throttle, int32_t& steering_wheel) override {
             if (movement == BRAKE || movement == ACCELERATE)
                 throttle = movement;
             else
                 steering_wheel = movement;
         }

        void stop(int32_t movement, int32_t& throttle, int32_t& steering_wheel) override {
            if (movement == BRAKE || movement == ACCELERATE)
                throttle = NOT_PRESSED;
            else
                steering_wheel = NOT_PRESSED;
        }
};


#endif //MICROMACHINES_CARON_H
