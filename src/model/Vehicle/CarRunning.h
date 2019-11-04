#ifndef MICROMACHINES_CARRUNNING_H
#define MICROMACHINES_CARRUNNING_H

#include "CarState.h"
#include <common/EntityType.h>

#define RADTODEG 57.295779513082320876f

class CarRunning : public CarState {

    public:
         void move(int32_t key, int32_t& key_v, int32_t& key_h) override {
             if (key == KEY_DOWN || key == KEY_UP)
                 key_v = key;
             else
                 key_h = key;
         }

        void stop(int32_t key, int32_t& key_v, int32_t& key_h) override {
            if (key == KEY_DOWN || key == KEY_UP)
                key_v = NOT_PRESSED;
            else
                key_h = NOT_PRESSED;
        }

};


#endif //MICROMACHINES_CARRUNNING_H
