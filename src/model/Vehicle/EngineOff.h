#ifndef MICROMACHINES_ENGINEOFF_H
#define MICROMACHINES_ENGINEOFF_H

#include "EngineState.h"

class EngineOff : public EngineState {

    public:
        void move(int32_t movement, int32_t& throttle, int32_t& steering_wheel)override {
            throttle = NOT_PRESSED;
            steering_wheel = NOT_PRESSED;
        }

        void stop(int32_t movement, int32_t& throttle, int32_t& steering_wheel) override {
            throttle = NOT_PRESSED;
            steering_wheel = NOT_PRESSED;
        }
};


#endif //MICROMACHINES_ENGINEOFF_H
