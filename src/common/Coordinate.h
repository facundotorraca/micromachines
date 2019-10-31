#ifndef MICROMACHINES_COORDINATE_H
#define MICROMACHINES_COORDINATE_H


class Coordinate {

    float x;
    float y;
    float angle;

    public:
        Coordinate(float x, float y, float angle);

        float get_x();

        float get_y();

        float get_angle();

};


#endif //MICROMACHINES_COORDINATE_H
