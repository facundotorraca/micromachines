#ifndef MICROMACHINES_FINISHLINE_H
#define MICROMACHINES_FINISHLINE_H

#include "Box2D/Box2D.h"
#include "model/Sensor.h"
#include "FirstFinishLine.h"
#include "SecondFinishLine.h"
#include <common/Coordinate.h>

class FinishLine {

    FirstFinishLine f_finish_line;
    SecondFinishLine s_finish_line;

    bool cross_first;
    bool cross_second;

    public:
        FinishLine(Coordinate begin, Coordinate end, b2World& track);

};


#endif //MICROMACHINES_FINISHLINE_H
