#ifndef MICROMACHINES_ALIVE_H
#define MICROMACHINES_ALIVE_H

#include "CarState.h"

#define MAX_ALLOWED_DISTANCE 2 //3 tiles

class Alive : public CarState {

    public:
        bool try_respawn(Coordinate respawn_point, b2Body* car_body, std::vector<Wheel*> wheels) override {
            return false;
        }

        void set_respawn_position(Coordinate& car_last_track_pos, Coordinate new_position) override {
            car_last_track_pos = new_position;
        }

};


#endif //MICROMACHINES_ALIVE_H
