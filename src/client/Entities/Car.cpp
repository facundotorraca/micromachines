//
// Created by javif on 17/10/2019.
//

#include "Car.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Car::draw(SDL_Point camera) {
    int x = (1280/2) + (posX-camera.x);
    int y = (720/2) + (posY-camera.y);
    SDL_Rect dst{x, y, 50, 100};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r) {
    this->tex = IMG_LoadTexture(rend, "/home/javier/Facultad/Taller/Micromachines/src/client/Entities/sprites/pitstop_car_1.png");
}
