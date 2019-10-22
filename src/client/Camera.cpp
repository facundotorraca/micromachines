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
    for (const auto& static_entity : background){
        static_entity->draw(camera, width, height);
    }
    for (const auto& entity : cars) {
        entity.second.draw(camera, width, height);
    }
}

void Camera::setOwnID(int32_t id) {
    this->my_car_ID = id;
}

void Camera::setTrack(int32_t id) {
    this->background.emplace_back(new Track(rend, id));
}

void
Camera::updateCar(int32_t car_id, int32_t carx, int32_t cary, int32_t carrot,
                                  int32_t w1x, int32_t w1y, int32_t w1rot,
                                  int32_t w2x, int32_t w2y, int32_t w2rot,
                                  int32_t w3x, int32_t w3y, int32_t w3rot,
                                  int32_t w4x, int32_t w4y, int32_t w4rot) {
    try {
        this->cars.at(car_id);
    } catch (std::out_of_range& e) {
        cars.emplace(car_id, rend);
    }

    if (car_id == this->my_car_ID)
        {camera.x = carx; camera.y = cary;}

    std::unique_lock<std::mutex> lock(mtx);
    cars.at(car_id).update_all(carx, cary, carrot,
                               w1x, w1y, w1rot,
                               w2x, w2y, w2rot,
                               w3x, w3y, w3rot,
                               w4x, w4y, w4rot);

}

void Camera::setRenderer(SDL_Renderer *pRenderer) {
    rend = pRenderer;
}
