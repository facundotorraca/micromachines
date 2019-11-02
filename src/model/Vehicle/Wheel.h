#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <set>
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include <model/Body.h>
#include <common/Coordinate.h>
#include <model/StaticTrackObject.h>

class Wheel : public Body {
    b2Body* wheel_body;
    b2Fixture* wheel_fixture{};

    float max_driver_force;
    float max_forward_speed;
    float max_backward_speed;
    float max_lateral_impulse;
    float traction_proportion;

    float speed_proportion;

    private:
        b2Vec2 get_lateral_velocity();

        b2Vec2 get_forward_velocity();

        void update_speed(uint8_t key);

        void update_friction();

    public:
        explicit Wheel(b2World& world, float max_forward_speed, float max_backward_speed, float max_driver_force, float max_lateral_impulse);

        Wheel(Wheel&& other_wheel) noexcept;

        void set_spawn_point(Coordinate spawn_point);

        void collide(Body* static_object) override;

        const b2Vec2& get_position();

        void update(uint8_t key);

        b2Body* get_body();

        float get_angle();

        int32_t get_ID() override;

        /*--------------Terrain Modifiers------------*/
        void set_traction(float proportion);

        void reduce_max_speed(float proportion);

        void set_max_traction();

        void set_max_speed();

        ~Wheel();
};
#endif //MICROMACHINES_WHEEL_H
