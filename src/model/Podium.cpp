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

void Podium::add_car(Car &car) {
    if (this->f_place_free) {
        std::cout << "1aa\n";
        car.move_to(this->f_place);
        this->f_place_free = false;
        return;
    }
    else if (this->s_place_free) {
        std::cout << "2aa\n";
        car.move_to(this->s_place);
        this->s_place_free = false;
        return;
    }
    else if (this->t_place_free) {
        std::cout << "3aa\n";
        car.move_to(this->t_place);
        this->t_place_free = false;
        return;
    }
}
