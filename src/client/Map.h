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
#include <memory>
#include "Camera.h"

struct Background{
    int32_t type;
    int32_t width;
    int32_t height;
};

class Map {
    std::list<Tile> tiles;
    Background back;
public:
    void draw(Camera& camera);
    void addTile(TileInfo& info);
    void setBackground(int32_t type, int32_t width, int32_t height);
};


#endif //MICROMACHINES_MAP_H
