//
// Created by javier on 6/11/19.
//

#include "Entities.h"

Entities::Entities() {

}

void Entities::addModifier(int32_t type, int32_t x, int32_t y) {
    uint64_t hash = (x << 31) | y;
    auto modifier = modifiers.emplace(hash, Modifier{type, x, y});
}

void Entities::removeModifier(int32_t x, int32_t y) {
    uint64_t hash = (x << 31) | y;
    modifiers.erase(hash);
}

void Entities::draw(Camera &camera) {
    auto size = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    for (auto& modifier : modifiers){
        camera.drawWorldTexture(modifier.second.type, modifier.second.x, modifier.second.y, size, size, 0);
    }
}
