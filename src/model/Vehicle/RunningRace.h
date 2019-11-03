#ifndef MICROMACHINES_RUNNINGRACE_H
#define MICROMACHINES_RUNNINGRACE_H

#include "RaceState.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define RADTODEG 57.295779513082320876f

class RunningRace : public RaceState {

    public:
        UpdateClient get_update(std::vector<Wheel*>& wheels, b2Body* car_body, int32_t ID) override {
            return UpdateClient({});
        }

};


#endif //MICROMACHINES_RUNNINGRACE_H
