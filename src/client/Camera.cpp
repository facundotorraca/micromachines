#include "Camera.h"
#include <client/Entities/Track.h>

Camera::Camera(SDL_Renderer* rend, int32_t x, int32_t y) :
    rend(rend),
    my_car_ID(-1),
    camera({0,0}),
    width(x), height(y)
{}

void Camera::draw() {
    std::unique_lock<std::mutex> lock(mtx);
    for (auto& static_entity : background){
        static_entity.draw(camera, width, height);
    }
    for (auto& entity : cars) {
        entity.second.draw(camera, width, height);
    }
}

void Camera::setOwnID(int32_t id) {
    this->my_car_ID = id;
}

void Camera::setTrack(int32_t id) {
    //this->background.emplace_back(new Track(rend, id));
}

void
Camera::updateCar(CarInfo info) {
    try {
        this->cars.at(info.car_id);
    } catch (std::out_of_range& e) {
        cars.emplace(info.car_id, rend);
    }

    if (info.car_id == this->my_car_ID)
        {camera.x = info.carx; camera.y = info.cary;}

    std::unique_lock<std::mutex> lock(mtx);
    cars.at(info.car_id).update_all(info);
}

void Camera::setRenderer(SDL_Renderer *pRenderer) {
    rend = pRenderer;
}

void Camera::addTile(TileInfo info) {
    background.emplace_back(rend, info);
}
