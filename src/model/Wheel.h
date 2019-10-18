#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <set>
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "RacingTrack.h"

class Wheel {
    b2Body *wheel_body;
    float max_forward_speed;
    float max_backward_speed;
    float max_lateral_impulse{};
    float max_driver_force;
    float current_traction{};
    //std::set<GroundAreaFUD*> m_groundAreas;

    private:
        b2Vec2 get_lateral_velocity();

        b2Vec2 get_forward_velocity();

        void update_drive(uint8_t key);

        void update_turn(uint8_t key);

        void update_friction();

    public:

        explicit Wheel(RacingTrack &racing_track, float max_forward_speed, float max_backward_speed, float max_driver_force);

        const b2Vec2& getPosition();

        float get_angle();

        void update(uint8_t key);

        ~Wheel();
};
#endif //MICROMACHINES_WHEEL_H
