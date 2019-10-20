#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H


#include "Entity.h"
#include "Wheel.h"
#include <SDL2/SDL.h>

class Car : public Entity {
    SDL_Texture* car_tex;
    Wheel wheel1;
    Wheel wheel2;
    Wheel wheel3;
    Wheel wheel4;
public:
    explicit Car(SDL_Renderer* r);

    void draw(SDL_Point camera) override;

    void update(std::vector<int32_t>& update_info) override;
};


#endif //MICROMACHINES_CAR_H
