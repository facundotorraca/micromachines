#include <vector>
#include <common/MsgTypes.h>
#include "RacingTrack.h"
#include "Box2D/Box2D.h"

RacingTrack::RacingTrack():
    racing_track(b2Vec2(0,0))
{
    this->width = 0;
    this->height = 0;
    this->velocity_iterations = 6;
    this->position_iterations = 2;
    this->time_step = 1.0f / 60.0f;
    this->track_terrain = TYPE_GRASS; //Default
    this->racing_track.SetContactListener(&this->contact_listener);
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
    std::vector<int32_t> map_info {MSG_SET_BACKGROUND ,this->track_terrain,
                                   this->height, this->width};
    p_socket.send(map_info);

    for (auto& terrain : this->terrains) {
        UpdateClient update_map = terrain->get_to_send();
        update_map.send(p_socket);
    }
    for (auto& object : this->static_track_objects) {
        UpdateClient update_map = object.get_to_send();
        update_map.send(p_socket);
    }

}

void RacingTrack::add_terrain(std::unique_ptr<Terrain>&& terrain) {
    this->terrains.push_back(std::move(terrain));
    this->terrains.back()->add_to_world(this->racing_track);
}

void RacingTrack::add_static_track_object(StaticTrackObject&& object) {
    this->static_track_objects.push_back(std::move(object));
    this->static_track_objects.back().add_to_world(this->racing_track);

}
void RacingTrack::set_track_size(int32_t height, int32_t width) {
    this->height = height;
    this->width = width;
}

void RacingTrack::set_track_terrain(int32_t terrain) {
    this->track_terrain = terrain;
}
