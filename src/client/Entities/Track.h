//
// Created by javier on 18/10/19.
//

#ifndef MICROMACHINES_TRACK_H
#define MICROMACHINES_TRACK_H

#include "Entity.h"

class Track : public Entity{
public:
    explicit Track(SDL_Renderer *rend, unsigned char i);
    void draw(SDL_Point camera) override;
};

#endif //MICROMACHINES_TRACK_H
