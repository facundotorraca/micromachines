#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <set>
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "WheelState.h"
#include <model/Body.h>
#include <common/Coordinate.h>
#include <model/StaticTrackObject.h>
#include <model/Modifiers/Effect.h>

#define DEGTORAD 0.0174532925199432957f

class Wheel : public Body {

    b2Body* wheel_body;
    WheelState wheel_state;

    float speed_proportion;
    float traction_proportion;

    private:
        b2Vec2 get_lateral_velocity();

        b2Vec2 get_forward_velocity();

        void update_speed(uint8_t key);

        void update_friction();

    public:
        explicit Wheel(b2World& world, float max_forward_speed, float max_backward_speed, float max_driver_force, float max_lateral_impulse);

        void set_spawn_point(Coordinate spawn_point);

        void collide(Body* static_object) override;

        void move_to(Coordinate coordinate);

        const b2Vec2& get_position();

        int32_t get_ID() override;

        void update(uint8_t key);

        b2Body* get_body();

        float get_angle();

    /*--------------Terrain & Modifiers------------*/
        void apply_effect(std::unique_ptr<Effect> effect);

        void reduce_max_traction(float proportion);

        void reduce_max_speed(float proportion);

        void restore_specs();

        ~Wheel();
};
#endif //MICROMACHINES_WHEEL_H
