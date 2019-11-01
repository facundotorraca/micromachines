#ifndef MICROMACHINES_SENSOR_H
#define MICROMACHINES_SENSOR_H

#include "Body.h"

class Sensor {
    public:
        virtual void apply_effect(Body* body) = 0;

        ~Sensor() = default;
};

#endif //MICROMACHINES_SENSOR_H
