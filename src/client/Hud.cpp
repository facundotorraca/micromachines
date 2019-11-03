//
// Created by javif on 01/11/2019.
//

#include "Hud.h"

void Hud::setHealth(int32_t h) {
    this->health = h;
}

void Hud::setSpeed(int32_t s) {
    this->speed = s*3.6/METER_TO_PIXEL;
}

void Hud::draw(Camera &camera) {
    /*---------------------------CREATE SPEEDOMETER---------------------------*/
    camera.drawTexture(SPEEDOMETER_TEX, 0.72, 0.07, 0.28);
    int show_speed = floor(speed);
    camera.drawText(std::to_string(show_speed)+" km/h", 0.76, 0.08, 0.6, 8);

    /*---------------------------CREATE HEALTH BAR----------------------------*/
    switch (health){
        case 0 ... 7:
            camera.drawTexture(HEALTH_16, 0.72, 0.14, 0.25); break;
        case 8 ... 13:
            camera.drawTexture(HEALTH_15, 0.72, 0.14, 0.25); break;
        case 14 ... 21:
            camera.drawTexture(HEALTH_14, 0.72, 0.14, 0.25); break;
        case 22 ... 27:
            camera.drawTexture(HEALTH_13, 0.72, 0.14, 0.25); break;
        case 28 ... 34:
            camera.drawTexture(HEALTH_12, 0.72, 0.14, 0.25); break;
        case 35 ... 40:
            camera.drawTexture(HEALTH_11, 0.72, 0.14, 0.25); break;
        case 41 ... 47:
            camera.drawTexture(HEALTH_10, 0.72, 0.14, 0.25); break;
        case 48 ... 53:
            camera.drawTexture(HEALTH_09, 0.72, 0.14, 0.25); break;
        case 54 ... 60:
            camera.drawTexture(HEALTH_08, 0.72, 0.14, 0.25); break;
        case 61 ... 67:
            camera.drawTexture(HEALTH_07, 0.72, 0.14, 0.25); break;
        case 68 ... 74:
            camera.drawTexture(HEALTH_06, 0.72, 0.14, 0.25); break;
        case 75 ... 80:
            camera.drawTexture(HEALTH_05, 0.72, 0.14, 0.25); break;
        case 81 ... 87:
            camera.drawTexture(HEALTH_04, 0.72, 0.14, 0.25); break;
        case 88 ... 93:
            camera.drawTexture(HEALTH_03, 0.72, 0.14, 0.25); break;
        case 94 ... 99:
            camera.drawTexture(HEALTH_02, 0.72, 0.14, 0.25); break;
        case 100:
            camera.drawTexture(HEALTH_01, 0.72, 0.14, 0.25); break;
    }

    /*---------------------------CREATE LAP COUNTER---------------------------*/
    std::string laps_text = std::string("Lap: ")+std::to_string(lap)+"/"+std::to_string(total_laps);
    camera.drawText(laps_text, 0.07, 0.07, 0.6, 7);
}

Hud::Hud() : health(100), lap(0), total_laps(0), speed(0){
}

void Hud::setLap(int32_t l) {
    this->lap = l;
}

void Hud::setTotalLaps(int32_t laps) {
    this->total_laps = laps;
}
