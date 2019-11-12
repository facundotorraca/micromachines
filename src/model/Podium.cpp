//
// Created by facundotorraca on 3/11/19.
//

#include "Podium.h"

Podium::Podium(Coordinate f_place, Coordinate s_place, Coordinate t_place):
    f_place(f_place),
    s_place(s_place),
    t_place(t_place)
{
    this->f_place_free = true;
    this->s_place_free = true;
    this->t_place_free = true;
}

void Podium::add_car(Car &car, int32_t ID) {
    if (this->podium.find(ID) != this->podium.end()) {
        car.move_to(this->podium.at(ID), true);
    } else {
        if (this->f_place_free) {
            car.move_to(this->f_place, true);
            this->f_place_free = false;
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, this->f_place));
            return;
        } else if (this->s_place_free) {
            car.move_to(this->s_place, true);
            this->s_place_free = false;
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, this->s_place));
            return;
        } else if (this->t_place_free) {
            car.move_to(this->t_place, true);
            this->t_place_free = false;
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, this->t_place));
            return;
        }
    }
}

void Podium::restart() {
    this->podium.clear();
    this->f_place_free = true;
    this->s_place_free = true;
    this->t_place_free = true;
}
