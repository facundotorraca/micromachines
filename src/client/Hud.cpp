//
// Created by javif on 01/11/2019.
//

#include "Hud.h"

void Hud::setHealth(int32_t h) {
    this->health = h;
}

void Hud::setSpeed(int32_t s) {
    this->speed = s;
}

void Hud::draw(Camera &camera) {
    camera.drawSpeedometer(speed);
    camera.drawHealthBar(health);
}
