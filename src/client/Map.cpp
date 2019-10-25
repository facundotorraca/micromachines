//
// Created by javier on 24/10/19.
//

#include "Map.h"

Map::Map() : my_car_id(-1){}

void Map::draw() {
    std::unique_lock<std::mutex> lock(mtx);
    camera.clear();
    for (auto& tile : tiles){
        tile.draw(camera);
    }
    for (auto& car : cars){
        car.second.draw(camera);
    }
    camera.draw();
}

void Map::addTile(TileInfo &info) {
    std::unique_lock<std::mutex> lock(mtx);
    tiles.emplace_back(info);
}

void Map::setOwnID(int32_t id) {
    this->my_car_id = id;
}

void Map::updateCar(CarInfo &info) {
    std::unique_lock<std::mutex> lock(mtx);
    try {
        this->cars.at(info.car_id);
    } catch (std::out_of_range& e) {
        cars.emplace(std::piecewise_construct,
                std::forward_as_tuple(info.car_id),
                std::forward_as_tuple());
    }
    if (info.car_id == this->my_car_id)
        camera.update(info.carx, info.cary);

    cars.at(info.car_id).update_all(info);
}
