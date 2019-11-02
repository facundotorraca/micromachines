//
// Created by javif on 30/10/2019.
//

#ifndef MICROMACHINES_SCENARIO_H
#define MICROMACHINES_SCENARIO_H

#include "Entities/TileInfo.h"
#include "Camera.h"
#include "Map.h"
#include "Entities/CarInfo.h"
#include "Hud.h"

class Scenario {
    Camera camera;
    Map map;
    Hud hud;
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
    void draw();
};


#endif //MICROMACHINES_SCENARIO_H
