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

    SDL_Rect w1dst{wheel_data[2],wheel_data[3], 17,50};
    SDL_RenderCopyEx(rend, wheel_tex, nullptr, &w1dst, wheel_data[4], nullptr, SDL_FLIP_NONE);
    SDL_Rect w2dst{wheel_data[5],wheel_data[6], 17,50};
    SDL_RenderCopyEx(rend, wheel_tex, nullptr, &w2dst, wheel_data[7], nullptr, SDL_FLIP_NONE);
    SDL_Rect w3dst{wheel_data[8],wheel_data[9], 17,50};
    SDL_RenderCopyEx(rend, wheel_tex, nullptr, &w3dst, wheel_data[10], nullptr, SDL_FLIP_NONE);
    SDL_Rect w4dst{wheel_data[11],wheel_data[12], 17,50};
    SDL_RenderCopyEx(rend, wheel_tex, nullptr, &w4dst, wheel_data[13], nullptr, SDL_FLIP_NONE);
    SDL_Rect dst{x, y, 200, 300};
    SDL_RenderCopyEx(rend, car_tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r) {
    std::cout << "Aca si Entre" << "\n";
    this->car_tex = IMG_LoadTexture(rend, "assets/sprites/autocopado.png");
    this->wheel_tex = IMG_LoadTexture(rend, "assets/sprites/wheel.png");
}

void Car::update(std::vector<int32_t> &update_info) {
    for (auto& data : update_info){
        wheel_data.emplace_back(data);
    }
}
