#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H


#include "Entity.h"
#include "Wheel.h"
#include <SDL2/SDL.h>

class Car : public Entity{
    Wheel wheel1;
    Wheel wheel2;
    Wheel wheel3;
    Wheel wheel4;
public:
    explicit Car(SDL_Renderer* r);

    void draw(SDL_Point camera, int32_t width, int32_t height) const override;

    void update_all(int32_t carx, int32_t cary, int32_t carrot,
                    int32_t w1x, int32_t w1y, int32_t w1rot, int32_t w2x,
                    int32_t w2y, int32_t w2rot, int32_t w3x, int32_t w3y,
                    int32_t w3rot, int32_t w4x, int32_t w4y, int32_t w4rot);
};


#endif //MICROMACHINES_CAR_H
