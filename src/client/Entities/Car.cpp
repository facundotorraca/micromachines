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
    int x = (WIDTH/2) + (posX-camera.x) - int(180/DRAW_SCALE/2);
    int y = (HEIGHT/2) + (posY-camera.y) - int(400/DRAW_SCALE/2);


    SDL_Rect dst{x, y, 180/DRAW_SCALE, 400/DRAW_SCALE};
    SDL_RenderCopyEx(rend, car_tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
    wheel1.draw(camera);
    wheel2.draw(camera);
    wheel3.draw(camera);
    wheel4.draw(camera);
}

Car::Car(SDL_Renderer* r) : Entity(r),
    wheel1(r), wheel2(r), wheel3(r), wheel4(r)
{
    std::cout << "Aca si Entre" << "\n";
    this->car_tex = IMG_LoadTexture(rend, "assets/sprites/autocopado.png");
}

void Car::update_all(std::vector<int32_t> &update_info) {
    this->update_position(update_info[3], update_info[4], update_info[5]);
    wheel1.update_position(update_info[6], update_info[7], update_info[8]);
    wheel2.update_position(update_info[9], update_info[10], update_info[11]);
    wheel3.update_position(update_info[12], update_info[13], update_info[14]);
    wheel4.update_position(update_info[15], update_info[16], update_info[17]);
}
