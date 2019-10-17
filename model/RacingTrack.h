#ifndef MICROMACHINES_RACINGTRACK_H
#define MICROMACHINES_RACINGTRACK_H

#include "Box2D/Box2D.h"

class RacingTrack {
    b2World racing_track;

    public:
        b2Body* add_car(b2BodyDef& car);


};


#endif //MICROMACHINES_RACINGTRACK_H
