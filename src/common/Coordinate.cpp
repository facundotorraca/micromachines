#include "Coordinate.h"

Coordinate::Coordinate(float x, float y, float angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
}

float Coordinate::get_x() {
    return this->x;
}

float Coordinate::get_y() {
    return this->y;
}

float Coordinate::get_angle() {
    return this->angle;
}
