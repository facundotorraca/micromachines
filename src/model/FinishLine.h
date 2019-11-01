#ifndef MICROMACHINES_FINISHLINE_H
#define MICROMACHINES_FINISHLINE_H

#include "model/Sensor.h"
#include <model/Terrains/Asphalt.h>

class FinishLine : public Sensor {

    b2Body* fl_body;
    b2Fixture * fl_fixture;

    public:
        FinishLine(Coordinate begin, Coordinate end, b2World& track);

        void apply_effect(Body *body) override;
};


#endif //MICROMACHINES_FINISHLINE_H
