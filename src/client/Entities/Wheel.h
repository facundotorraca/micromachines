#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include "Entity.h"

class Wheel : public Entity {
public:
    explicit Wheel(SDL_Renderer* r);
    void draw(SDL_Point camera, int32_t width, int32_t height) const override;
};


#endif //MICROMACHINES_WHEEL_H
