#ifndef MICROMACHINES_COORDINATE_H
#define MICROMACHINES_COORDINATE_H


class Coordinate {

    float x;
    float y;
    float angle;

    public:
        Coordinate(float x, float y, float angle);

        bool is_adjacent_to(Coordinate other);

        float get_x();

        float get_y();

        float get_angle();

};


#endif //MICROMACHINES_COORDINATE_H
