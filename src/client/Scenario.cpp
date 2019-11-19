//
// Created by javif on 30/10/2019.
//

#include "Scenario.h"

Scenario::Scenario(Bot& bot) : bot(bot), my_car_id(-1) {}

void Scenario::addTile(TileInfo &info) {
    bot.add_tile(info);
    map.addTile(info);
    minimap.addTile(info);
}

void Scenario::addDynamicObject(int32_t ID, int32_t type, int32_t x, int32_t y) {
    dyn_entities.emplace(std::piecewise_construct,  std::forward_as_tuple(ID), std::forward_as_tuple(type, x, y));
}

void Scenario::setOwnID(int32_t id) {
    bot.set_id(id);
    this->my_car_id = id;
    minimap.setMyID(id);
}

void Scenario::updateCar(CarInfo &info, Camera& camera) {
    bot.update_car(info);
    auto car = cars.emplace(std::piecewise_construct,
                            std::forward_as_tuple(info.car_id),
                            std::forward_as_tuple(info.car_id));
    if (car.second){
        minimap.addCar(info.car_id, info.carx, info.cary);
    } else {
        minimap.updateCar(info.car_id, info.carx, info.cary);
        cars.at(info.car_id).updateAll(info, sound);
    }
    if (info.car_id == this->my_car_id){
        camera.update(info.carx, info.cary, info.carvel, info.carrot);
        hud.setSpeed(info.carvel);
        sound.center(info.carx, info.cary);
    }
}

void Scenario::updateDynamicObject(int32_t ID, int32_t x, int32_t y) {
    this->dyn_entities.at(ID).update_position(x, y, 0);
}

void Scenario::draw(Camera& camera) {
    map.draw(camera);
    entities.draw(camera);

    for (auto& car : cars)
        car.second.draw(camera);

    for (auto& dyn_object : dyn_entities)
        dyn_object.second.draw(camera);

    hud.draw(camera);
    countdown.draw(camera);
    screen_effect.draw(camera);
    minimap.draw(camera);
    l_screen.draw(camera);
}

void Scenario::setCarHealth(int32_t id, int32_t health) {
    try{
        cars.at(id);
    } catch (std::out_of_range& e) {
        std::cerr << "setCarHealth: invalid ID" << std::endl;
    }
    if (id == this->my_car_id){
        hud.setHealth(health);
    }

    cars.at(id).setHealth(health, sound);
}

void Scenario::setBackground(int32_t type, int32_t width, int32_t height) {
    map.setBackground(type, width, height);
    minimap.setSize(width, height);
}

void Scenario::setLapNumber(int32_t lap) {
    hud.setLap(lap);
}

void Scenario::setTotalLaps(int32_t laps) {
    hud.setTotalLaps(laps);
}

void Scenario::setLoadingScreen(bool show) {
    if (show){
        l_screen.show();
    } else {
        l_screen.hide();
        sound.playBackgroundMusic();
    }
}

void Scenario::showCountdownNumber(int32_t number) {
    countdown.show(number);
    sound.playCountdownSound(number);
}

void Scenario::addModifier(int32_t type, int32_t x, int32_t y) {
    entities.addModifier(type, x, y);
}

void Scenario::removeModifier(int32_t x, int32_t y) {
    entities.removeModifier(x, y);
}

void Scenario::addFinishedPlayer(std::string& player_name) {
    hud.addFinishedPlayer(player_name);
}

void Scenario::showScreenEffect(int32_t effect, int32_t duration) {
    screen_effect.show(effect, duration);
    sound.playEffectSound(effect);
}

void Scenario::setRacePosition(int32_t number) {
    hud.setRacePosition(number);
}

void Scenario::reset() {
    hud.reset();
}

void Scenario::removeCar(int32_t id) {
    cars.erase(id);
    minimap.removeCar(id);
}

Scenario::~Scenario() = default;

