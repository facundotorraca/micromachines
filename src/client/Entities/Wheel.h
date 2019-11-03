#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include <client/Camera.h>
#include <client/Camera.h>
#include "Entity.h"

class Wheel : public Entity {
    public:
        void draw(Camera& camera) override {
            camera.drawWorldTexture(WHEEL_TEX, posX, posY, rot);
        }
};

#endif //MICROMACHINES_WHEEL_H
