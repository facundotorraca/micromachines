#include <vector>
#include <random>
#include "Podium.h"
#include "RacingTrack.h"
#include <common/MsgTypes.h>
#include <server/MapLoader.h>
#include "StaticTrackObject.h"
#include <common/EntityType.h>
#include <common/ProtectedQueue.h>

size_t get_random_position(size_t max_position) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, max_position);
    return dist(mt);
}

RacingTrack::RacingTrack(std::string& map_path, std::string& map_name):
    racing_track(b2Vec2(0,0)),
    map_loader(map_path, map_name)
{
    this->podium = nullptr;
    this->finish_line = nullptr;

    /*--------HYPERPARAMS----------*/
    this->velocity_iterations = 6;
    this->position_iterations = 2;
    this->time_step = 1.0f / 60.0f;

    this->racing_track.SetContactListener(&this->contact_listener);
}

void RacingTrack::update() {
    this->racing_track.Step(this->time_step,
                      this->velocity_iterations,
                      this->position_iterations);
}

void RacingTrack::add_terrain(std::unique_ptr<Terrain>&& terrain) {
    this->terrains.push_back(std::move(terrain));
    this->terrains.back()->add_to_world(this->racing_track);
}

void RacingTrack::add_track(std::unique_ptr<Terrain>&& track_part) {
    this->track.push_back(std::move(track_part));
    this->track.back()->add_to_world(this->racing_track);
}

void RacingTrack::add_static_track_object(StaticTrackObject&& object) {
    this->static_track_objects.push_back(std::move(object));
    this->static_track_objects.back().add_to_world(this->racing_track);
}

void RacingTrack::set_finish_line(Coordinate begin, Coordinate end) {
    this->finish_line = new FinishLine(begin, end, this->racing_track);
}

void RacingTrack::set_podium(Coordinate f_place, Coordinate s_place, Coordinate t_place) {
    this->podium = new Podium(f_place, s_place, t_place);
}

void RacingTrack::add_car(Car &car) {
    car.add_to_world(this->racing_track);
}

void RacingTrack::add_car_to_podium(Car &car, int32_t ID) {
    if (this->podium)
        this->podium->add_car(car, ID);
}

void RacingTrack::add_spawn_point(Coordinate spawn_point) {
    this->spawn_points.push_back(spawn_point);
}

void RacingTrack::set_spawn_points_to_cars(std::unordered_map<int32_t, Car> &cars) {
    int spawn_point_pos = (int)this->spawn_points.size() - 1; //Start from end to beginning
    for (auto &car : cars) {
        car.second.move_to(this->spawn_points[spawn_point_pos]);
        spawn_point_pos--;
    }
}

Coordinate RacingTrack::get_random_track_position() {
    int random_position = get_random_position(this->track.size()-1);
    return this->track.at(random_position)->get_map_coordinate();
}

void RacingTrack::add_modifier(const std::shared_ptr<Modifier>& modifier) {
    modifier->add_to_world(this->racing_track);
}

void RacingTrack::prepare_track(ClientUpdater &updater) {
    this->map_loader.load_map(*this, updater);
}

RacingTrack::~RacingTrack() {
    delete this->podium;
    delete this->finish_line;
}

void RacingTrack::restart() {
    if (this->podium)
        this->podium->restart();

}

