#include <cmath>
#include "Coordinate.h"
#include <model/Orientation.h>

float get_orientation_angle(Orientation orientation) {
    switch (orientation) {
        case UP:
            return 180;
        case DOWN:
            return 0;
        case RIGHT:
            return 270;
        case LEFT:
            return 90;
        case NOT_ORIENTED:
            return 0;
    }
}

Coordinate::Coordinate(float x, float y, Orientation orientation) {
    this->x = x;
    this->y = y;
    this->orientation = orientation;
    this->angle = get_orientation_angle(this->orientation);
}

Coordinate::Coordinate(float x, float y) {
    this->x = x;
    this->y = y;
    this->angle = 0;
    this->orientation = NOT_ORIENTED;
}

Coordinate::Coordinate(float x, float y, float angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->orientation = NOT_ORIENTED;
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

