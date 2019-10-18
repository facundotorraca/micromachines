//
// Created by javif on 17/10/2019.
//

#include "Car.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

void Car::draw() {
    SDL_Rect dst{posX, posY, 50, 100};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r) {
    this->tex = IMG_LoadTexture(rend, "/home/javier/Facultad/Taller/Micromachines/src/client/Entities/sprites/pitstop_car_1.png");
    if (!tex) {
        std::cout << "Cague" << std::endl;
    }
}

