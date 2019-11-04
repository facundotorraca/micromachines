#ifndef MICROMACHINES_CARSTOPPED_H
#define MICROMACHINES_CARSTOPPED_H

#include "CarState.h"

class CarStopped : public CarState {

    public:
        void move(int32_t key, int32_t& key_v, int32_t& key_h) override {}

        void stop(int32_t key, int32_t& key_v, int32_t& key_h) override {}

};


#endif //MICROMACHINES_CARSTOPPED_H
