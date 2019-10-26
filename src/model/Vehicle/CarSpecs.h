#ifndef MICROMACHINES_CARSPECS_H
#define MICROMACHINES_CARSPECS_H

typedef struct {
    float max_forward_speed;
    float max_backward_speed;
    float back_wheel_max_force;
    float front_wheel_max_force;
    float back_max_lateral_impulse;
    float front_max_lateral_impulse;
} CarSpecs;

#endif //MICROMACHINES_CARSPECS_H
