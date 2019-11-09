#include "PositionManager.h"
#include <common/MsgTypes.h>

PositionManager::PositionManager(std::unordered_map<int32_t, Car> &cars):
    cars(cars)
{}

void PositionManager::update(LapCounter& lap_counter) {
    if (this->cars.empty())
        return;

    for (auto& car : this->cars) {
        Position position{car.first, lap_counter.get_laps(car.first), car.second.get_begin_distance()};
        this->positions_sorter.push(position);
    }

    for (size_t i = 0; i < positions_sorter.size(); i++) {
        auto position = positions_sorter.top();
        try {
            this->positions.at(position.ID) = i + 1;
        } catch(const std::out_of_range& e) {
            this->positions.insert(std::pair<int32_t, int32_t>(position.ID, i+1));
        }
        positions_sorter.pop();
    }
}

int32_t PositionManager::get_position(int32_t ID) {
    try {
        return this->positions.at(ID);
    } catch(const std::out_of_range& e) {
        return 1;
   }
}

void PositionManager::send_update(int32_t ID, ClientUpdater &updater) {
    try {
        UpdateClient position_info(std::vector<int32_t>{MSG_SET_POSITION, this->positions.at(ID)});
        updater.send_to(ID, position_info);
    } catch (const std::out_of_range &e) {
        UpdateClient position_info(std::vector<int32_t>{MSG_SET_POSITION, 1});
        updater.send_to(ID, position_info);
    }
}