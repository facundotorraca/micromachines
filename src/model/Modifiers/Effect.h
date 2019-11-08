#ifndef MICROMACHINES_EFFECT_H
#define MICROMACHINES_EFFECT_H

#include <cstdint>
#include <iostream>

class Effect {

    protected:
        int32_t life;

        float lateral_impulse_modifier;
        float backward_speed_modifier;
        float forward_speed_modifier;
        float driver_force_modifier;

    public:
        explicit Effect(float lateral_impulse_modifier, float backward_speed_modifier, float forward_speed_modifier, float driver_force_modifier, int32_t duration) {
            this->lateral_impulse_modifier = lateral_impulse_modifier;
            this->backward_speed_modifier = backward_speed_modifier;
            this->forward_speed_modifier = forward_speed_modifier;
            this->driver_force_modifier = driver_force_modifier;
            this->life = duration;
        }

        float apply_to_lateral_impulse(float lateral_impulse) {
            return this->lateral_impulse_modifier * lateral_impulse;
        }

        float apply_to_backward_speed(float backward_speed) {
            return this->backward_speed_modifier * backward_speed;
        }

        float apply_to_forward_speed(float forward_speed) {
            return this->forward_speed_modifier * forward_speed;
        }

        float apply_to_driver_force(float driver_force) {
            return this->driver_force_modifier * driver_force;
        }

        virtual void update() {
            this->life -= 1;
        }

        bool is_over() {
            return this->life == 0;
        }

        virtual std::unique_ptr<Effect> get_next_effect() = 0;
};

#endif //MICROMACHINES_EFFECT_H
