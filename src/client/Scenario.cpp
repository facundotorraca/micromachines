//
// Created by javif on 30/10/2019.
//

#include "Scenario.h"

Scenario::Scenario() : my_car_id(-1) {}

void Scenario::addTile(TileInfo &info) {
    std::unique_lock<std::mutex> lock(mtx);
    map.addTile(info);
    minimap.addTile(info);
}

void Scenario::setOwnID(int32_t id) {
    this->my_car_id = id;
    minimap.setMyID(id);
}

void Scenario::updateCar(CarInfo &info) {
    std::unique_lock<std::mutex> lock(mtx);
    auto car = cars.emplace(std::piecewise_construct,
                            std::forward_as_tuple(info.car_id),
                            std::forward_as_tuple());
    if (car.second){
        minimap.addCar(info.car_id, info.carx, info.cary);
    } else {
        minimap.updateCar(info.car_id, info.carx, info.cary);
        cars.at(info.car_id).update_all(info);
    }
    if (info.car_id == this->my_car_id){
        camera.update(info.carx, info.cary, info.carvel, info.carrot);
        hud.setSpeed(info.carvel);
    }
}

void Scenario::draw() {
    mtx.lock();
    camera.clear();
    map.draw(camera);
    entities.draw(camera);
    for (auto& car : cars){
        car.second.draw(camera);
    }
    hud.draw(camera);
    countdown.draw(camera);
    minimap.draw(camera);
    l_screen.draw(camera);
    mtx.unlock();
    camera.draw();
}

void Scenario::setCarHealth(int32_t id, int32_t health) {
    std::unique_lock<std::mutex> lock(mtx);
    try{
        cars.at(id);
    } catch (std::out_of_range& e) {
        std::cerr << "setCarHealth: invalid ID" << std::endl;
    }
    if (id == this->my_car_id)
        hud.setHealth(health);

    cars.at(id).setHealth(health);
}

void Scenario::setBackground(int32_t type, int32_t width, int32_t height) {
    std::unique_lock<std::mutex> lock(mtx);
    map.setBackground(type, width, height);
    minimap.setSize(width, height);
}

void Scenario::setLapNumber(int32_t lap) {
    std::unique_lock<std::mutex> lock(mtx);
    hud.setLap(lap);
}

void Scenario::setTotalLaps(int32_t laps) {
    std::unique_lock<std::mutex> lock(mtx);
    hud.setTotalLaps(laps);
}

void Scenario::setLoadingScreen(bool show) {
    std::unique_lock<std::mutex> lock(mtx);
    if (show){
        l_screen.show();
    } else {
        l_screen.hide();
    }
}

void Scenario::showCountdownNumber(int32_t number) {
    std::unique_lock<std::mutex> lock(mtx);
    countdown.show(number);
}

void Scenario::addModifier(int32_t type, int32_t x, int32_t y) {
    std::unique_lock<std::mutex> lock(mtx);
    entities.addModifier(type, x, y);
}

void Scenario::removeModifier(int32_t x, int32_t y) {
    std::unique_lock<std::mutex> lock(mtx);
    entities.removeModifier(x, y);
}

void Scenario::addFinishedPlayer(std::string& player_name) {
    hud.addFinishedPlayer(player_name);
}

void Scenario::showScreenEffect(int32_t effect) {
    screen_effect.show(effect);
}

