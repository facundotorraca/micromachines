#include "Wheel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define HEIGHT 720
#define WIDTH 1280

Wheel::Wheel(SDL_Renderer* r) : Entity(r) {
    std::cout << "Entre" << "\n";
    this->tex = IMG_LoadTexture(rend, "assets/sprites/wheel.png");
}

void Wheel::draw(SDL_Point camera) {
    int x = (WIDTH/2) + (posX-camera.x) - int(17/DRAW_SCALE/2);
    int y = (HEIGHT/2) + (posY-camera.y) - int(50/DRAW_SCALE/2);
    SDL_Rect dst{x, y, 17/DRAW_SCALE, 50/DRAW_SCALE};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}
