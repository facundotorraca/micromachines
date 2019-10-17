#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <set>
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "RacingTrack.h"

class Wheel {
    b2Body *wheel_body;
    b2Body* m_body;
    float m_maxForwardSpeed;
    float m_maxBackwardSpeed;
    float m_maxDriveForce;
    float m_maxLateralImpulse;
    //std::set<GroundAreaFUD*> m_groundAreas;
    float m_currentTraction;


    private:
        b2Vec2 get_lateral_velocity();

        b2Vec2 get_forward_velocity();

    public:
        explicit Wheel(RacingTrack &racing_track);

        void update_drive(Key controlState);

        void updateTurn(Key controlState);

        void updateFriction();

        ~Wheel();
};
#endif //MICROMACHINES_WHEEL_H
