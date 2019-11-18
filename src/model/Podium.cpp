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

    this->current_unranked_place = 0;
}

void Podium::add_car(Car &car, int32_t ID) {
    if (this->podium.find(ID) != this->podium.end()) {
       if (!this->on_podium.at(ID)) {
           bool car_moved = car.move_to(this->podium.at(ID), true);
           this->on_podium.at(ID) = car_moved;
       }
    } else {
        if (this->f_place_free) {
            bool car_moved = car.move_to(this->f_place, true);
            this->f_place_free = false;
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, this->f_place));
            this->on_podium.emplace(std::pair<int32_t, bool>(ID, car_moved));
            return;
        } else if (this->s_place_free) {
            bool car_moved = car.move_to(this->s_place, true);
            this->s_place_free = false;
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, this->s_place));
            this->on_podium.emplace(std::pair<int32_t, bool>(ID, car_moved));
            return;
        } else if (this->t_place_free) {
            bool car_moved = car.move_to(this->t_place, true);
            this->t_place_free = false;
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, this->t_place));
            this->on_podium.emplace(std::pair<int32_t, bool>(ID, car_moved));
            return;
        } else {
            Coordinate unranked_place = this->unranked_places.at(this->current_unranked_place);
            bool car_moved = car.move_to(unranked_place,true);
            this->podium.emplace(std::pair<int32_t, Coordinate >(ID, unranked_place));
            this->on_podium.emplace(std::pair<int32_t, bool>(ID, car_moved));
            this->current_unranked_place++;
            return;
        }
    }
}

void Podium::restart() {
    this->podium.clear();
    this->on_podium.clear();
    this->f_place_free = true;
    this->s_place_free = true;
    this->t_place_free = true;
    this->current_unranked_place = 0;
}

void Podium::add_unranked_place(Coordinate unranked_place) {
    this->unranked_places.push_back(unranked_place);
}
