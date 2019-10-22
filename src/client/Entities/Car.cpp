#include "Car.h"
#include <SDL2/SDL.h>
#include "common/Sizes.h"
#include <SDL2/SDL_image.h>

void Car::draw(SDL_Point camera, int32_t width, int32_t height) const {
    int x = (width/2) + (posX-camera.x);
    int y = (height/2) + (posY-camera.y);

    wheel1.draw(camera, width, height);
    wheel2.draw(camera, width, height);
    wheel3.draw(camera, width, height);
    wheel4.draw(camera, width, height);

    SDL_Rect dst{x, y, int(CAR_WIDTH * METER_TO_PIXEL), int(CAR_HEIGHT * METER_TO_PIXEL)};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r),
    wheel1(r), wheel2(r), wheel3(r), wheel4(r)
{
    this->tex = IMG_LoadTexture(rend, "assets/sprites/Cars/Car red striped/Car red striped front.png");
}

void Car::update_all(int32_t carx, int32_t cary, int32_t carrot,
                     int32_t w1x, int32_t w1y, int32_t w1rot, int32_t w2x,
                     int32_t w2y, int32_t w2rot, int32_t w3x, int32_t w3y,
                     int32_t w3rot, int32_t w4x, int32_t w4y, int32_t w4rot) {

    posX = carx; posY = cary; rot = carrot;
    wheel1.update_position(w1x, w1y, w1rot);
    wheel2.update_position(w2x, w2y, w2rot);
    wheel3.update_position(w3x, w3y, w3rot);
    wheel4.update_position(w4x, w4y, w4rot);
}
