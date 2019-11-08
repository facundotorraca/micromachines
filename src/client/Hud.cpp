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
    camera.drawScreenTexture(SPEEDOMETER_TEX, 0.72, 0.07, 0.28);
    int show_speed = floor(speed);
    camera.drawText(std::to_string(show_speed)+" km/h", 0.76, 0.08, 0.6, 8);

    /*---------------------------CREATE HEALTH BAR----------------------------*/
    switch (health){
        case 0 ... 7:
            camera.drawScreenTexture(HEALTH_16, 0.72, 0.14, 0.25); break;
        case 8 ... 13:
            camera.drawScreenTexture(HEALTH_15, 0.72, 0.14, 0.25); break;
        case 14 ... 21:
            camera.drawScreenTexture(HEALTH_14, 0.72, 0.14, 0.25); break;
        case 22 ... 27:
            camera.drawScreenTexture(HEALTH_13, 0.72, 0.14, 0.25); break;
        case 28 ... 34:
            camera.drawScreenTexture(HEALTH_12, 0.72, 0.14, 0.25); break;
        case 35 ... 40:
            camera.drawScreenTexture(HEALTH_11, 0.72, 0.14, 0.25); break;
        case 41 ... 47:
            camera.drawScreenTexture(HEALTH_10, 0.72, 0.14, 0.25); break;
        case 48 ... 53:
            camera.drawScreenTexture(HEALTH_09, 0.72, 0.14, 0.25); break;
        case 54 ... 60:
            camera.drawScreenTexture(HEALTH_08, 0.72, 0.14, 0.25); break;
        case 61 ... 67:
            camera.drawScreenTexture(HEALTH_07, 0.72, 0.14, 0.25); break;
        case 68 ... 74:
            camera.drawScreenTexture(HEALTH_06, 0.72, 0.14, 0.25); break;
        case 75 ... 80:
            camera.drawScreenTexture(HEALTH_05, 0.72, 0.14, 0.25); break;
        case 81 ... 87:
            camera.drawScreenTexture(HEALTH_04, 0.72, 0.14, 0.25); break;
        case 88 ... 93:
            camera.drawScreenTexture(HEALTH_03, 0.72, 0.14, 0.25); break;
        case 94 ... 99:
            camera.drawScreenTexture(HEALTH_02, 0.72, 0.14, 0.25); break;
        case 100:
            camera.drawScreenTexture(HEALTH_01, 0.72, 0.14, 0.25); break;
    }

    /*---------------------------CREATE LAP COUNTER---------------------------*/
    std::string laps_text = std::string("Lap: ")+std::to_string(lap)+"/"+std::to_string(total_laps);
    camera.drawText(laps_text, 0.07, 0.07, 0.6, 7);

    /*--------------------------DRAW FINISHED PLAYERS-------------------------*/
    int i = 1;
    for (auto& name : scoreboard){
        auto show_name = std::to_string(i) + ": " + name;
        camera.drawText(show_name, 0.07, 0.07+(0.04*i), 0.4, show_name.size());
        ++i;
    }
}

Hud::Hud() : health(100), lap(0), total_laps(0), speed(0){
}

void Hud::setLap(int32_t l) {
    this->lap = l;
}

void Hud::setTotalLaps(int32_t laps) {
    this->total_laps = laps;
}

void Hud::addFinishedPlayer(std::string &player_name) {
    scoreboard.emplace_back(player_name);
}
