#ifndef MICROMACHINES_CARSPECS_H
#define MICROMACHINES_CARSPECS_H

#include <vector>

class CarSpecs {
    float max_forward_speed;
    float max_backward_speed;
    float back_wheel_max_force;
    float front_wheel_max_force;
    float back_max_lateral_impulse;
    float front_max_lateral_impulse;

    public:
        CarSpecs(float max_forward_speed,
                 float max_backward_speed,
                 float back_wheel_max_force,
                 float front_wheel_max_force,
                 float back_max_lateral_impulse,
                 float front_max_lateral_impulse);

        float get_max_forward_speed();

        float get_max_backward_speed();

        float get_back_wheel_max_force();

        float get_front_wheel_max_force();

        float get_back_max_lateral_impulse();

        float get_front_max_lateral_impulse();
};


#endif //MICROMACHINES_CARSPECS_H
