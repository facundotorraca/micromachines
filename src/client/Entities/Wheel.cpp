#include "Wheel.h"
#include <SDL2/SDL.h>
#include "common/Sizes.h"
#include <SDL2/SDL_image.h>

Wheel::Wheel(SDL_Renderer* r) : Entity(r) {
    this->tex = IMG_LoadTexture(rend, "assets/sprites/wheel.png");
}

void Wheel::draw(SDL_Point camera) {
    int x = (WIDTH_SCREEN/2) + (posX-camera.x) - int((WIDTH_WHEEL * METER_TO_PIXEL)/2);
    int y = (HEIGHT_SCREEN/2) + (posY-camera.y) - int((HEIGHT_WHEEL * METER_TO_PIXEL)/2);
    SDL_Rect dst{x, y, int(WIDTH_WHEEL * METER_TO_PIXEL), int(HEIGHT_WHEEL * METER_TO_PIXEL)};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}
