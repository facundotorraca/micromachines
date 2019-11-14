//
// Created by javier on 6/11/19.
//

#include "Entities.h"

Entities::Entities() {}

/*-----------OLD HASH FUNCTION---------------*/
/*             good but slow                 */
/*-------------------------------------------*/
/*
uint64_t hash_coord(int32_t x, int32_t y) {
    x = (x | (x << 31)) & 0xFFFF00000000FFFF;
    x = (x | (x << 17)) & 0x00FF0000FF0000FF;
    x = (x | (x << 7))  & 0xF00F00F00F00F00F;
    x = (x | (x << 3))  & 0x30C30C30C30C30C3;
    x = (x | (x << 1))  & 0x9249249249249249;

    y = (y | (y << 31)) & 0xFFFF00000000FFFF;
    y = (y | (y << 15)) & 0x00FF0000FF0000FF;
    y = (y | (y << 7))  & 0xF00F00F00F00F00F;
    y = (y | (y << 3))  & 0x30C30C30C30C30C3;
    y = (y | (y << 1))  & 0x9249249249249249;

    return  x | (y << 1);
} */

uint64_t hash_coord(int32_t x, int32_t y) {
    return (x * 0x1f1f1f1f) ^ y;
}

void Entities::addModifier(int32_t type, int32_t x, int32_t y) {
    uint64_t hash = hash_coord(x,y);
    auto modifier = modifiers.emplace(hash, Modifier{type, x, y});
}

void Entities::removeModifier(int32_t x, int32_t y) {
    uint64_t hash = hash_coord(x,y);
    modifiers.erase(hash);
}

void Entities::draw(Camera &camera) {
    for (auto& modifier : modifiers){
        auto size = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
        switch (modifier.second.type){
            case TYPE_BOOST:
            case TYPE_FIX:
                size /= 2;
                break;
        }
        camera.drawWorldTexture(modifier.second.type, modifier.second.x, modifier.second.y, size, size, 0);
    }
}
