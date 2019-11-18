#ifndef MICROMACHINES_ENGINEON_H
#define MICROMACHINES_ENGINEON_H

#include "EngineState.h"
#include <common/EntityType.h>

#define RADTODEG 57.295779513082320876f

class EngineOn : public EngineState {

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


#endif //MICROMACHINES_ENGINEON_H
