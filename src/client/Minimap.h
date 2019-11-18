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
#include <SDL2/SDL.h>
#include <unordered_map>

#define MINIMAP_WIDTH 0.12f
#define MINIMAP_HEIGHT 0.213f

struct MiniCar {
    float x;
    float y;
};

class Minimap{
    int32_t my_car_id;
    int32_t size_x;
    int32_t size_y;
    std::unordered_map<int32_t, MiniCar>cars;
    SDL_Surface* surface;
    SDL_Surface* white_s;
    SDL_Surface* black_s;
public:
    Minimap();
    void setMyID(int32_t id);
    void addTile(TileInfo& info);
    void updateCar(int32_t id, int32_t x, int32_t y);
    void addCar(int32_t id, int32_t x, int32_t y);
    void removeCar(int32_t id);
    void draw(Camera& camera);
    void setSize(int32_t w, int32_t h);
    ~Minimap();
};


#endif //MICROMACHINES_MINIMAP_H
