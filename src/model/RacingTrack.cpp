#include <vector>
#include "RacingTrack.h"
#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

RacingTrack::RacingTrack():
    racing_track(b2Vec2(0,0))
{
    this->velocity_iterations = 6;
    this->position_iterations = 2;
    this->time_step = 1.0f / 60.0f;
}

b2Body* RacingTrack::add_body(b2BodyDef& body) {
    return this->racing_track.CreateBody(&body);
}

void RacingTrack::update() {
    this->racing_track.Step(this->time_step, this->velocity_iterations, this->position_iterations);
}

b2World& RacingTrack::get_world() {
    return this->racing_track;
}

void RacingTrack::send(ProtocolSocket& p_socket) {
    for (auto& terrain : this->terrains) {
        UpdateClient update_map = terrain->get_to_send();
        update_map.send(p_socket);
    }
}

void RacingTrack::add_map_part(std::unique_ptr<Terrain>&& terrain) {
    this->terrains.push_back(std::move(terrain));
}
