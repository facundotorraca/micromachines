#include "RacingTrack.h"

b2Body* RacingTrack::add_car(b2BodyDef& car) {
    return this->racing_track.CreateBody(&car);
}
