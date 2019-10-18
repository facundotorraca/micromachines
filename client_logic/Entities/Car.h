//
// Created by javif on 17/10/2019.
//

#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H


#include "Entity.h"
#include <SDL2/SDL.h>

class Car : public Entity {
public:
    explicit Car(SDL_Renderer* r);
    void draw() override;
};


#endif //MICROMACHINES_CAR_H
