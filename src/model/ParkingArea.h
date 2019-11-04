#ifndef MICROMACHINES_PARKINGAREA_H
#define MICROMACHINES_PARKINGAREA_H


#include <vector>
#include <common/Coordinate.h>
#include <model/Vehicle/Car.h>

class ParkingArea {

    int current_parking_pos;
    std::vector<Coordinate> parking_area;

    public:
        explicit ParkingArea(std::vector<Coordinate>&& parking_area);

        void park_car(Car& car);


};


#endif //MICROMACHINES_PARKINGAREA_H
