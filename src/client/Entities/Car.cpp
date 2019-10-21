#include "Car.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "common/Sizes.h"
#include <SDL2/SDL_image.h>

void Car::draw(SDL_Point camera) {
    int x = (WIDTH_SCREEN/2) + (posX-camera.x);
    int y = (HEIGHT_SCREEN/2) + (posY-camera.y);

    wheel1.draw(camera);
    wheel2.draw(camera);
    wheel3.draw(camera);
    wheel4.draw(camera);

    SDL_Rect dst{x, y, int(CAR_WIDTH * METER_TO_PIXEL), int(CAR_HEIGHT * METER_TO_PIXEL)};
    SDL_RenderCopyEx(rend, car_tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Car::Car(SDL_Renderer* r) : Entity(r),
    wheel1(r), wheel2(r), wheel3(r), wheel4(r)
{
    this->car_tex = IMG_LoadTexture(rend, "assets/sprites/autocopado.png");
}

void Car::update_all(std::vector<int32_t> &update_info) {
    this->update_position(update_info[3], update_info[4], update_info[5]);
    wheel1.update_position(update_info[6], update_info[7], update_info[8]);
    wheel2.update_position(update_info[9], update_info[10], update_info[11]);
    wheel3.update_position(update_info[12], update_info[13], update_info[14]);
    wheel4.update_position(update_info[15], update_info[16], update_info[17]);
}
