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
#include "Bot.h"
#include "Entities/DynamicEntity.h"
#include "SoundSystem.h"

class Scenario {
    Bot& bot;
    Map map;
    Hud hud;
    LoadingScreen l_screen;
    Countdown countdown;
    ScreenEffectDrawer screen_effect;
    Minimap minimap;
    Entities entities;
    SoundSystem sound;
    int32_t my_car_id;
    std::unordered_map<int32_t, Car> cars;
    std::unordered_map<int32_t, DynamicEntity> dyn_entities;
    std::mutex mtx;
public:
    explicit Scenario(Bot& bot);
    void addTile(TileInfo& info);
    void addDynamicObject(int32_t ID, int32_t type, int32_t x, int32_t y);
    void setOwnID(int32_t id);
    void updateCar(CarInfo& info, Camera& camera);
    void setCarHealth(int32_t id, int32_t health);
    void setBackground(int32_t type, int32_t width, int32_t height, Camera& camera);
    void setLapNumber(int32_t lap);
    void setTotalLaps(int32_t laps);
    void setLoadingScreen(bool show);
    void showCountdownNumber(int32_t number);
    void addModifier(int32_t type, int32_t x, int32_t y);
    void removeModifier(int32_t x, int32_t y);
    void addFinishedPlayer(std::string& player_name);
    void updateDynamicObject(int32_t ID, int32_t x, int32_t y);
    void showScreenEffect(int32_t effect, int32_t duration);
    void setRacePosition(int32_t number);
    void draw(Camera& camera);
    void reset();

    void removeCar(int32_t id);
    ~Scenario();
};


#endif //MICROMACHINES_SCENARIO_H
