#include "Wheel.h"
#include <SDL2/SDL.h>
#include "common/Sizes.h"
#include <SDL2/SDL_image.h>

#include <iostream>

Wheel::Wheel(SDL_Renderer* r) : Entity(r) {
    this->rect = {0, 0, int(WIDTH_WHEEL * METER_TO_PIXEL), int(HEIGHT_WHEEL * METER_TO_PIXEL)};
    this->tex = IMG_LoadTexture(rend, "assets/sprites/wheel_3.png");
}

void Wheel::draw(SDL_Point camera, int32_t width, int32_t height) {
    rect.x = (width/2) + (posX-camera.x);
    rect.y = (height/2) + (posY-camera.y);
    SDL_RenderCopyEx(rend, tex, nullptr, &rect, rot, nullptr, SDL_FLIP_NONE);
}
