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

bool Coordinate::is_adjacent_to(Coordinate other) {
    if (other.x != this->x && other.y != this->y)
        return false;
    if (other.x == this->x)
        return (other.y + 1 == this->y) || (other.y - 1 == this->y);
    else
        return (other.x + 1 == this->x) || (other.x - 1 == this->x);
}