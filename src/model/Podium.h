#ifndef MICROMACHINES_PODIUM_H
#define MICROMACHINES_PODIUM_H

#include <common/Coordinate.h>
#include <model/Vehicle/Car.h>

class Podium {

    bool f_place_free;
    bool s_place_free;
    bool t_place_free;

    Coordinate f_place;
    Coordinate s_place;
    Coordinate t_place;

    public:
        Podium(Coordinate f_place, Coordinate s_place, Coordinate t_place);

        void add_car(Car& car);
};


#endif //MICROMACHINES_PODIUM_H
