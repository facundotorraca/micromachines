#ifndef MICROMACHINES_COORDINATE_H
#define MICROMACHINES_COORDINATE_H

#include <model/Orientation.h>

class Coordinate {

    float x;
    float y;
    float angle;
    Orientation orientation;

    public:
        Coordinate(float x, float y, Orientation angle);

        Coordinate(float x, float y, float angle);

        Coordinate(float x, float y);

        bool is_adjacent_to(Coordinate other);

        float get_x();

        float get_y();

        float get_angle();

        float x_distance_with(Coordinate other);

        float y_distance_with(Coordinate other);

};


#endif //MICROMACHINES_COORDINATE_H
