//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_TILE_H
#define MICROMACHINES_TILE_H


#include <client/Commands/TileInfo.h>
#include <common/Sizes.h>
#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Tile : public Entity{
    TileInfo info;
public:
    Tile(SDL_Renderer* rend, TileInfo info) : Entity(rend), info(info){
        this->tex = IMG_LoadTexture(rend, "assets/sprites/Track/Grass/land_grass04.png");
    }
    void draw(SDL_Point camera, int32_t width, int32_t height) const override {
        int x = (width/2) + (posX-camera.x);
        int y = (height/2) + (posY-camera.y);
        SDL_Rect dst{x, y, int(WIDTH_TILE * METER_TO_PIXEL), int(HEIGHT_TILE * METER_TO_PIXEL)};
        SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
    }

};
#endif //MICROMACHINES_TILE_H
