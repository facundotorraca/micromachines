#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H


#include "Entity.h"
#include "Wheel.h"
#include "CarInfo.h"
#include <SDL2/SDL.h>

class Car : public Entity{
    Wheel wheel1;
    Wheel wheel2;
    Wheel wheel3;
    Wheel wheel4;
public:
    explicit Car(SDL_Renderer* r);

    void draw(SDL_Point camera, int32_t width, int32_t height) override;

    void update_all(CarInfo& info);
};


#endif //MICROMACHINES_CAR_H
