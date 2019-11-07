#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <client/Camera.h>
#include <client/Camera.h>
#include "Entity.h"

class Wheel : public Entity {
    public:
        void draw(Camera& camera) override {
            int32_t size_w = WIDTH_WHEEL*METER_TO_PIXEL;
            int32_t size_h = HEIGHT_WHEEL*METER_TO_PIXEL;
            camera.drawWorldTexture(WHEEL_TEX, posX, posY, size_w, size_h, rot);
        }
};

#endif //MICROMACHINES_WHEEL_H
