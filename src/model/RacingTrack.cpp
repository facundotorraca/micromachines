#include "RacingTrack.h"
#include "Box2D/Box2D.h"

RacingTrack::RacingTrack(b2Vec2& gravity):
    racing_track(gravity)
{
    this->velocity_iterations = 6;
    this->position_iterations = 2;
    this->time_step = 1.0f / 60.0f;
}

b2Body* RacingTrack::add_car(b2BodyDef& car) {
    return this->racing_track.CreateBody(&car);
}

void RacingTrack::update() {
    this->racing_track.Step(this->time_step, this->velocity_iterations, this->position_iterations);
}
