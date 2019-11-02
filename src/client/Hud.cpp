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
    camera.drawLapNumber(lap, total_laps);
}

Hud::Hud() : health(100), lap(0), total_laps(0), speed(0){
}

void Hud::setLap(int32_t l) {
    this->lap = l;
}

void Hud::setTotalLaps(int32_t laps) {
    this->total_laps = laps;
}
