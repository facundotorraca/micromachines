#include "ParkingArea.h"
#include <model/Vehicle/Car.h>

ParkingArea::ParkingArea(std::vector<Coordinate> &&parking_area):
    parking_area(std::move(parking_area))
{
    this->current_parking_pos = 0;
}

void ParkingArea::park_car(Car &car) {}


