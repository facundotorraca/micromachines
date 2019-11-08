#include "Race.h"
#include <unordered_map>
#include <common/MsgTypes.h>
#include <server/ClientUpdater.h>

#define SPAWN_PROBABILITY 0.003f//0.0015f

Race::Race(int32_t total_laps,  std::string map_path, std::string map_name):
        lap_counter(total_laps),
        racing_track(map_path, map_name),
        modifier_spawner(SPAWN_PROBABILITY, this->racing_track)
{}

void Race::add_car_with_specs(int32_t ID, CarSpecs specs) {
    this->cars.emplace(std::piecewise_construct, std::forward_as_tuple(ID),
                                                 std::forward_as_tuple(specs));

    this->racing_track.add_car(this->cars.at(ID));
}

void Race::send_info_to_player(int32_t ID, ClientUpdater& client_updater) {
    client_updater.send_to(ID, UpdateClient({MSG_BEGIN_LOADING}));
    this->racing_track.send(client_updater, ID);
    client_updater.send_to(ID, UpdateClient({MSG_TOTAL_LAPS, this->lap_counter.get_total_laps()}));
    client_updater.send_to(ID, UpdateClient({MSG_CAR_ID, ID}));
    client_updater.send_to(ID, UpdateClient({MSG_FINISH_LOADING}));
}

void Race::start() {
    for (auto &car : this->cars) {
        car.second.turn_on();
    }
}

void Race::update() {
    for (auto& car : this->cars) {
        car.second.update();
        car.second.modify_laps(this->lap_counter, car.first);
        if (this->lap_counter.car_complete_laps(car.first))
            this->racing_track.add_car_to_podium(car.second, car.first );
    }
    this->modifier_spawner.update();
    this->racing_track.update();
}

void Race::update_cars(UpdateRace update) {
    update.update_cars(this->cars);
}

bool Race::car_complete_laps(int32_t ID) {
    return this->lap_counter.car_complete_laps(ID);
}

void Race::player_left_game(const int32_t ID) {
    this->cars.erase(ID);
}

void Race::prepare() {
    for (auto &car : this->cars) {
        this->running_cars.emplace(std::pair<int32_t, Car&>(car.first, car.second));
    }
    this->racing_track.set_spawn_points_to_cars(this->cars);
}

void Race::send_general_updates_of_player(int32_t ID, ClientUpdater& updater) {
    this->cars.at(ID).send_general_update(ID, updater);
    this->modifier_spawner.send_modifiers_update(updater);
    this->lap_counter.send_update(ID, updater);
}

