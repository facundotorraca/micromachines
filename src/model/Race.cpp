#include "Race.h"
#include <unordered_map>
#include <common/MsgTypes.h>
#include <server/ClientUpdater.h>

#define SPAWN_PROBABILITY 0.003f//0.0015f

Race::Race(int32_t total_laps,  std::string map_path, std::string map_name):
    lap_counter(total_laps),
    position_manager(this->cars),
    racing_track(map_path, map_name),
    modifier_spawner(SPAWN_PROBABILITY, this->racing_track)
{}

void Race::add_car_with_specs(int32_t ID, CarSpecs specs) {
    this->cars.emplace(std::piecewise_construct, std::forward_as_tuple(ID),
                                                 std::forward_as_tuple(specs));

    this->racing_track.add_car(this->cars.at(ID));
}

void Race::send_info_to_player(int32_t ID, ClientUpdater& client_updater) {
    this->lap_counter.send_total_laps(ID, client_updater);
    client_updater.send_to(ID, UpdateClient(std::vector<int32_t>{MSG_CAR_ID, ID}));
}

void Race::start() {
    for (auto& car : this->cars) {
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
    this->position_manager.update(this->lap_counter);
}

void Race::update_cars(UpdateRace update) {
    update.update_cars(this->cars);
}

bool Race::car_complete_laps(int32_t ID) {
    return this->lap_counter.car_complete_laps(ID);
}

void Race::player_left_game(const int32_t ID) {
    this->racing_track.remove_car(this->cars.at(ID));
    this->cars.erase(ID);
}

void Race::prepare(ClientUpdater& updater) {
    updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_BEGIN_LOADING}));
    this->racing_track.prepare_track(updater);
    this->racing_track.set_spawn_points_to_cars(this->cars);
    updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_FINISH_LOADING}));
}

void Race::send_updates(int32_t ID, ClientUpdater& updater) {
    this->cars.at(ID).send_updates(ID, updater);
    this->modifier_spawner.send_modifiers_update(updater);
    this->lap_counter.send_update(ID, updater);
    this->position_manager.send_update(ID, updater);
}

void Race::get_dto_data(DTO_Info &info) {
    size_t i = 0;
    for (auto& car : this->cars) {
        car.second.get_dto_info(car.first, info.car_info[i]);
        this->position_manager.get_dto_info(car.first, info.car_info[i]);
        i++;
    }

    info.cars = this->cars.size();
    this->lap_counter.get_dto_info(info);
}

void Race::apply_plugin(DTO_Info &info) {
    for (size_t i = 0; i < info.cars; i++)
        this->cars.at(info.car_info[i].ID).apply_plugin(info.car_info[i]);
}

void Race::restart() {
    this->lap_counter.restart();
    this->racing_track.restart();
    this->position_manager.restart();
    this->racing_track.set_spawn_points_to_cars(this->cars);

    for (auto& car : this->cars) {
        car.second.repair();
    }
}
