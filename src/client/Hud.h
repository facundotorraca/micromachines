//
// Created by javif on 01/11/2019.
//

#ifndef MICROMACHINES_HUD_H
#define MICROMACHINES_HUD_H


#include "Camera.h"

class Hud {
    int32_t health;
    int32_t lap;
    int32_t total_laps;
    int32_t speed;
    bool finished;
    int32_t frames_drawed_effect;
    std::string race_position;
    std::list<std::string> scoreboard;
public:
    Hud();
    void draw(Camera& camera);
    void setHealth(int32_t h);
    void setSpeed(int32_t s);
    void setLap(int32_t lap);
    void setTotalLaps(int32_t laps);
    void addFinishedPlayer(std::string &player_name);
    void setRacePosition(int32_t position);

    void reset();
};


#endif //MICROMACHINES_HUD_H
