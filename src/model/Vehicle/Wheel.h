#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <set>
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include <model/FixtureUserData.h>

class Wheel {
    b2Body* wheel_body;
    b2Fixture* wheel_fixture{};

    float max_driver_force;
    float max_forward_speed;
    float max_backward_speed;
    float max_lateral_impulse;
    float traction_proportion;

    float speed_proportion;

    FixtureUserData* wheel_user_data{};

    private:
        b2Vec2 get_lateral_velocity();

        b2Vec2 get_forward_velocity();

        void update_speed(uint8_t key);

        void update_friction();

    public:
        explicit Wheel(b2World& world, float max_forward_speed, float max_backward_speed, float max_driver_force, float max_lateral_impulse);

        Wheel(Wheel&& other_wheel) noexcept;

        const b2Vec2& get_position();

        void update(uint8_t key);

        b2Body* get_body();

        float get_angle();

        /*--------------Terrain Modifiers------------*/
        void set_traction(float proportion);

        void reduce_max_speed(float proportion);

        void set_max_traction();

        void set_max_speed();

        ~Wheel();
};
#endif //MICROMACHINES_WHEEL_H
