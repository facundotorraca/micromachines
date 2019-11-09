#ifndef MICROMACHINES_CAROFF_H
#define MICROMACHINES_CAROFF_H

#include "CarState.h"

class CarOff : public CarState {

    public:
        void move(int32_t movement, int32_t& throttle, int32_t& steering_wheel)override {}

        void stop(int32_t movement, int32_t& throttle, int32_t& steering_wheel) override {}
};


#endif //MICROMACHINES_CAROFF_H
