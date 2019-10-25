//
// Created by javier on 24/10/19.
//

#include "Map.h"

Map::Map() : my_car_id(-1){}

void Map::draw() {
    camera.clear();
    add_mtx.lock();
    for (auto& tile : tiles){
        tile.draw(camera);
    }
    add_mtx.unlock();
    add_mtx.lock();
    for (auto& car : cars){
        std::unique_lock<std::mutex> draw_lock(draw_mtx);
        car.second.draw(camera);
    }
    add_mtx.unlock();
    camera.draw();
}

void Map::addTile(TileInfo &info) {
    std::unique_lock<std::mutex> lock(add_mtx);
    tiles.emplace_back(info);
}

void Map::setOwnID(int32_t id) {
    this->my_car_id = id;
}

void Map::updateCar(CarInfo &info) {
    try {
        this->cars.at(info.car_id);
    } catch (std::out_of_range& e) {
        std::unique_lock<std::mutex> lock(add_mtx);
        cars.emplace(std::piecewise_construct,
                std::forward_as_tuple(info.car_id),
                std::forward_as_tuple());
    }
    if (info.car_id == this->my_car_id)
        camera.update(info.carx, info.cary);

    std::unique_lock<std::mutex> lock(draw_mtx);
    cars.at(info.car_id).update_all(info);
}
