#include "Car.h"
#include <SDL2/SDL.h>
#include "common/Sizes.h"
#include <SDL2/SDL_image.h>

void Car::draw(SDL_Point camera, int32_t width, int32_t height) {
    rect.x = (width/2) + (posX-camera.x);
    rect.y = (height/2) + (posY-camera.y);

    wheel1.draw(camera, width, height);
    wheel2.draw(camera, width, height);
    wheel3.draw(camera, width, height);
    wheel4.draw(camera, width, height);

    SDL_RenderCopyEx(rend, tex, nullptr, &rect, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r),
    wheel1(r), wheel2(r), wheel3(r), wheel4(r){
    this->rect = {0, 0, int(CAR_WIDTH * METER_TO_PIXEL), int(CAR_HEIGHT * METER_TO_PIXEL)};
    this->tex = IMG_LoadTexture(rend, "assets/sprites/Cars/Car red striped/Car red striped front.png");
}

void Car::update_all(CarInfo& info) {

    posX = info.carx; posY = info.cary; rot = info.carrot;
    wheel1.update_position(info.w1x, info.w1y, info.w1rot);
    wheel2.update_position(info.w2x, info.w2y, info.w2rot);
    wheel3.update_position(info.w3x, info.w3y, info.w3rot);
    wheel4.update_position(info.w4x, info.w4y, info.w4rot);
}
