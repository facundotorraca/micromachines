//
// Created by javif on 17/10/2019.
//

#include "Car.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define HEIGHT 720
#define WIDTH 1280

void Car::draw(SDL_Point camera) {
    int x = (WIDTH/2) + (posX-camera.x) - int(50/2);
    int y = (HEIGHT/2) + (posY-camera.y) - int(100/2);


    SDL_Rect dst{x, y, 50, 100};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r) {
    std::cout << "Aca si Entre" << "\n";
    this->tex = IMG_LoadTexture(rend, "assets/sprites/autocopado.png");
}
