//
// Created by javier on 3/11/19.
//

#ifndef MICROMACHINES_MINIMAP_H
#define MICROMACHINES_MINIMAP_H

#include <map>
#include <list>
#include "Entities/CarInfo.h"
#include "Entities/TileInfo.h"
#include <common/Sizes.h>
#include "Camera.h"

struct MiniCar{
    double x;
    double y;
};

struct MiniTile{
    double x;
    double y;
};

class Minimap {
    int32_t my_car_id;
    int32_t size_x;
    int32_t size_y;
    std::map<int32_t, MiniCar>cars;
    std::list<MiniTile>tiles;
public:
    Minimap() : my_car_id(-1), size_x(1), size_y(1){}
    void setMyID(int32_t id){
        my_car_id = id;
    }
    void addTile(TileInfo& info){
        if (info.type >= 3 && info.type <= 27)
            tiles.emplace_back(MiniTile{((0.2f*info.posx)/size_x), ((0.2f*info.posy)/size_y)+0.8});
    }
    void updateCar(CarInfo& info){
        try{
            cars.at(info.car_id);
        } catch (std::out_of_range& e){
            auto new_car = MiniCar{((0.2f*info.carx)/size_x), ((0.2f*info.cary)/size_y)+0.8};
            cars.emplace(info.car_id, new_car);
        }
        cars.at(info.car_id).x = 0.2f*info.carx/size_x;
        cars.at(info.car_id).y = 0.2f*info.cary/size_y + 0.8;
    }
    void draw(Camera& camera){/*
        for (auto& tile : tiles)
            camera.drawTexture(WHITE_BLOCK, tile.x, tile.y, 0.4);
        for (auto& car : cars)
            camera.drawTexture(RED_DOT, car.second.x, car.second.y, 0.5);*/
    }
    void setSize(int32_t w, int32_t h){
        size_x = w*TILE_TERRAIN_SIZE*METER_TO_PIXEL;
        size_y = h*TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    }
};


#endif //MICROMACHINES_MINIMAP_H
