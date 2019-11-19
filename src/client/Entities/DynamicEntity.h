#ifndef MICROMACHINES_DYNAMICENTITY_H
#define MICROMACHINES_DYNAMICENTITY_H

#include <cstdint>
#include "Entity.h"

class DynamicEntity : public Entity {

    int32_t dyn_tex;

    public:
        DynamicEntity(int32_t type, int32_t x, int32_t y) {
            this->posX = x;
            this->posY = y;
            this->rot = 0;
            this->dyn_tex = type;
        }

        void draw(Camera& camera) override {
            int32_t size_w = TILE_TERRAIN_SIZE * METER_TO_PIXEL;
            int32_t size_h = TILE_TERRAIN_SIZE * METER_TO_PIXEL;
            camera.drawWorldTexture(dyn_tex, posX, posY,  size_w,  size_h, rot);
        }


};


#endif //MICROMACHINES_DYNAMICENTITY_H
