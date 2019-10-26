//
// Created by facundotorraca on 18/10/19.
//

#include "CarSpecs.h"

CarSpecs::CarSpecs(float max_forward_speed, float max_backward_speed, float back_wheel_max_force,
                   float front_wheel_max_force, float back_max_lateral_impulse, float front_max_lateral_impulse):
    max_forward_speed(max_forward_speed),
    max_backward_speed(max_backward_speed),
    back_wheel_max_force(back_wheel_max_force),
    front_wheel_max_force(front_wheel_max_force),
    back_max_lateral_impulse(back_max_lateral_impulse),
    front_max_lateral_impulse(front_max_lateral_impulse)
{}

float CarSpecs::get_max_forward_speed() {
    return this->max_forward_speed;
}

float CarSpecs::get_max_backward_speed() {
    return this->max_backward_speed;
}

float CarSpecs::get_back_wheel_max_force() {
    return this->back_wheel_max_force;
}

float CarSpecs::get_front_wheel_max_force() {
    return this->front_wheel_max_force;
}

float CarSpecs::get_back_max_lateral_impulse() {
    return this->back_max_lateral_impulse;
}

float CarSpecs::get_front_max_lateral_impulse() {
    return this->front_max_lateral_impulse;
}


