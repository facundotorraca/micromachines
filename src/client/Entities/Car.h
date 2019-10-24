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
public:
    void draw(Camera& camera) override {
        wheel1.draw(camera);
        wheel2.draw(camera);
        wheel3.draw(camera);
        wheel4.draw(camera);
        camera.drawCar(posX, posY, rot);
    }

    void update_all(CarInfo& info) {
        posX = info.carx; posY = info.cary; rot = info.carrot;
        wheel1.update_position(info.w1x, info.w1y, info.w1rot);
        wheel2.update_position(info.w2x, info.w2y, info.w2rot);
        wheel3.update_position(info.w3x, info.w3y, info.w3rot);
        wheel4.update_position(info.w4x, info.w4y, info.w4rot);
    }
};


#endif //MICROMACHINES_CAR_H
