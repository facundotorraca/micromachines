#ifndef MICROMACHINES_FIRSTFINISHLINE_H
#define MICROMACHINES_FIRSTFINISHLINE_H

#include "Sensor.h"
#include <common/Coordinate.h>
#include <Box2D/Dynamics/b2Fixture.h>

class FirstFinishLine : public Sensor {

    b2Body* fl_body;
    b2Fixture * fl_fixture;

    bool& cross_first;
    bool& cross_second;

    public:
        FirstFinishLine(Coordinate begin, Coordinate end, bool& cross_first ,bool& cross_second, b2World& track);

        void apply_effect(Body* body) override;


};


#endif //MICROMACHINES_FIRSTFINISHLINE_H
