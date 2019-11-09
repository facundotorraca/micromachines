//
// Created by javif on 30/10/2019.
//

#ifndef MICROMACHINES_SCENARIO_H
#define MICROMACHINES_SCENARIO_H

#include "Camera.h"
#include "Map.h"
#include "Entities/CarInfo.h"
#include "Hud.h"
#include "LoadingScreen.h"
#include "Countdown.h"
#include "Minimap.h"
#include "Entities.h"
#include "Entities/TileInfo.h"
#include "ScreenEffectDrawer.h"
#include "PauseMenu.h"

class Scenario {
    Camera camera;
    Map map;
    Hud hud;
    LoadingScreen l_screen;
    Countdown countdown;
    ScreenEffectDrawer screen_effect;
    Minimap minimap;
    Entities entities;
    PauseMenu pause_menu;
    int32_t my_car_id;
    std::map<int32_t, Car> cars;
    std::mutex mtx;
public:
    Scenario();
    void addTile(TileInfo& info);
    void setOwnID(int32_t id);
    void updateCar(CarInfo& info);
    void setCarHealth(int32_t id, int32_t health);
    void setBackground(int32_t type, int32_t width, int32_t height);
    void setLapNumber(int32_t lap);
    void setTotalLaps(int32_t laps);
    void setLoadingScreen(bool show);
    void showCountdownNumber(int32_t number);
    void addModifier(int32_t type, int32_t x, int32_t y);
    void removeModifier(int32_t x, int32_t y);
    void addFinishedPlayer(std::string& player_name);
    void showScreenEffect(int32_t effect, int32_t duration);
    void addConnectionLostMessage();
    void setRacePosition(int32_t number);
    void draw();
    void togglePause();
    bool quit();
};


#endif //MICROMACHINES_SCENARIO_H
