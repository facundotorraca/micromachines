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
    int x = (WIDTH/2) + (posX-camera.x) - int(200/2);
    int y = (HEIGHT/2) + (posY-camera.y) - int(300/2);

    wheel1.draw(camera);
    wheel2.draw(camera);
    wheel3.draw(camera);
    wheel4.draw(camera);

    SDL_Rect dst{x, y, 200, 300};
    SDL_RenderCopyEx(rend, car_tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r),
    wheel1(r), wheel2(r), wheel3(r), wheel4(r)
{
    std::cout << "Aca si Entre" << "\n";
    this->car_tex = IMG_LoadTexture(rend, "assets/sprites/autocopado.png");
}

void Car::update(std::vector<int32_t> &update_info) {
    this->posX = update_info[2];
    this->posY = update_info[3];
    this->rot = update_info[4];
    wheel1.update(update_info[5], update_info[6], update_info[7]);
    wheel2.update(update_info[8], update_info[9], update_info[10]);
    wheel3.update(update_info[11], update_info[12], update_info[13]);
    wheel4.update(update_info[14], update_info[15], update_info[16]);
}
