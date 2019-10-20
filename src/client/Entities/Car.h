#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H


#include "Entity.h"
#include <SDL2/SDL.h>

class Car : public Entity {
    SDL_Texture* car_tex;
    SDL_Texture* wheel_tex;
    std::vector<int32_t> wheel_data{};
public:
    explicit Car(SDL_Renderer* r);

    void draw(SDL_Point camera) override;

    void update(std::vector<int32_t>& update_info) override;
};


#endif //MICROMACHINES_CAR_H
