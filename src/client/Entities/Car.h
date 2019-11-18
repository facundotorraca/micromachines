#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <client/Camera.h>
#include "Entity.h"
#include "Wheel.h"
#include "CarInfo.h"

class Car : public Entity{
    Wheel wheel1;
    Wheel wheel2;
    Wheel wheel3;
    Wheel wheel4;
    int32_t health = 100;
    float i = 0;
public:
    void draw(Camera& camera) override {
        wheel1.draw(camera);
        wheel2.draw(camera);
        wheel3.draw(camera);
        wheel4.draw(camera);
        int32_t size_w = CAR_WIDTH * METER_TO_PIXEL;
        int32_t size_h = CAR_HEIGHT * METER_TO_PIXEL;
        if (health <= 0){
            camera.drawWorldTexture(WRECKED_CAR_TEX, posX, posY, size_w, size_h, rot);
            if (i <= 7)
                camera.drawWorldTexture(EXPLOSION_TEX+(int)i, posX, posY, size_w, size_w, rot);
            i+=0.08;
        } else {
            i = 0;
            if (health <= 50) {
                camera.drawWorldTexture(DMG_CAR_TEX, posX, posY, size_w, size_h,
                                        rot);
            } else {
                camera.drawWorldTexture(CAR_TEX, posX, posY, size_w, size_h,
                                        rot);
            }
        }
    }

    void update_all(CarInfo& info) {
        posX = info.carx; posY = info.cary; rot = info.carrot;
        wheel1.update_position(info.w1x, info.w1y, info.w1rot);
        wheel2.update_position(info.w2x, info.w2y, info.w2rot);
        wheel3.update_position(info.w3x, info.w3y, info.w3rot);
        wheel4.update_position(info.w4x, info.w4y, info.w4rot);
    }

    void setHealth(int32_t health){
        this->health = health;
    }
};


#endif //MICROMACHINES_CAR_H
