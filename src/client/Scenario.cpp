//
// Created by javif on 30/10/2019.
//

#include "Scenario.h"

Scenario::Scenario() : my_car_id(-1) {}

void Scenario::addTile(TileInfo &info) {
    std::unique_lock<std::mutex> lock(mtx);
    map.addTile(info);
}

void Scenario::setOwnID(int32_t id) {
    this->my_car_id = id;
}

void Scenario::updateCar(CarInfo &info) {
    std::unique_lock<std::mutex> lock(mtx);
    try {
        this->cars.at(info.car_id);
    } catch (std::out_of_range& e) {
        cars.emplace(std::piecewise_construct,
                     std::forward_as_tuple(info.car_id),
                     std::forward_as_tuple());
    }
    if (info.car_id == this->my_car_id)
        camera.update(info.carx, info.cary, info.carrot);

    cars.at(info.car_id).update_all(info);
}

void Scenario::draw() {
    std::unique_lock<std::mutex> lock(mtx);
    camera.clear();
    map.draw(camera);
    for (auto& car : cars){
        car.second.draw(camera);
    }
    camera.draw();
}

void Scenario::setCarHealth(int32_t id, int32_t health) {
    std::unique_lock<std::mutex> lock(mtx);
    try{
        cars.at(id);
    } catch (std::out_of_range& e) {
        std::cerr << "setCarHealth: invalid ID" << std::endl;
    }

    cars.at(id).setHealth(health);
}

void Scenario::setBackground(int32_t type, int32_t width, int32_t height) {
    std::unique_lock<std::mutex> lock(mtx);
    map.setBackground(type, width, height);
}
