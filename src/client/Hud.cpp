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
    /*---------------------------DRAW SPEEDOMETER-----------------------------*/
    camera.drawScreenTexture(SPEEDOMETER_TEX, 0.72, 0.07, 0.28);
    int show_speed = floor(speed);
    camera.drawText(std::to_string(show_speed)+" KM/H", 0.76, 0.08, 0.6, 8);

    /*---------------------------DRAW HEALTH BAR------------------------------*/
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

    /*---------------------------DRAW LAP COUNTER-----------------------------*/
    
    if (!finished){
        std::string laps_text = std::string("LAP: ")+
                std::to_string(lap)+"/"+std::to_string(total_laps);
        camera.drawText(laps_text, 0.07, 0.07, 0.6, 7);
    }

    if (finished){
        if (frames_drawed_effect <= 172){
            camera.drawFullScreenTexture(CONFETTI_TEX+(frames_drawed_effect/4)%43);
            frames_drawed_effect++;
        }
    }

    /*--------------------------DRAW FINISHED PLAYERS-------------------------*/
    int i = 1;
    for (auto& name : scoreboard){
        auto show_name = std::to_string(i) + ": " + name;
        camera.drawText(show_name, 0.07, 0.2+(0.04*i),
                0.4, show_name.size());
        ++i;
    }

    /*--------------------------DRAW RACE POSITION----------------------------*/

    camera.drawText(race_position, 0.07, 0.14, 1.6, 2);

}

Hud::Hud() : health(100), lap(0), total_laps(0), speed(0), 
            finished(false), frames_drawed_effect(0), race_position("?"){}

void Hud::setLap(int32_t l) {
    this->lap = l;
    if (lap > total_laps){
        this->finished = true;
    }
}

void Hud::setTotalLaps(int32_t laps) {
    this->total_laps = laps;
}

void Hud::addFinishedPlayer(std::string &player_name) {
    scoreboard.emplace_back(player_name);
}

std::string stringify(int32_t number){
    std::string n(std::to_string(number));
    int last_digit = number%10;
    switch (last_digit){
        case 1: return n+"st";
        case 2: return n+"nd";
        case 3: return n+"rd";
        default: return n+"th";
    }
}

void Hud::setRacePosition(int32_t position) {
    if (position == (-1)){
        race_position = "?";
    } else {
        this->race_position = stringify(position);
    }
}

void Hud::reset() {
    scoreboard.clear();
    finished = false;
    frames_drawed_effect = 0;
    lap = 0;
}

