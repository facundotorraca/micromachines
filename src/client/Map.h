//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_MAP_H
#define MICROMACHINES_MAP_H

#include "Entities/CarInfo.h"
#include "Entities/TileInfo.h"
#include "Entities/Tile.h"
#include "Entities/Car.h"
#include <mutex>
#include <map>
#include <list>
#include "Camera.h"

class Map {
    Camera camera;
    int32_t my_car_id;
    std::map<int32_t, Car> cars;
    std::list<Tile> tiles;
    std::mutex mtx;
public:
    Map();
    void draw();
    void addTile(TileInfo& info);
    void setOwnID(int32_t id);
    void updateCar(CarInfo& info);
    void setTrack(int32_t id){}
};


#endif //MICROMACHINES_MAP_H
