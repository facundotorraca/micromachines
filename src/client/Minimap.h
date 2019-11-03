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
    SDL_Surface* surface;
    SDL_Surface* white_s;
public:
    Minimap() : my_car_id(-1), size_x(1), size_y(1) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        surface = SDL_CreateRGBSurface(0, 300, 300, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
        surface = SDL_CreateRGBSurface(0, 300, 300, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
        white_s = SDL_CreateRGBSurface(0, 7, 7, 32, 0, 0, 0, 0);
        SDL_FillRect(white_s, nullptr,
                     SDL_MapRGB(white_s->format, 255, 255, 255));
    }
    void setMyID(int32_t id){
        my_car_id = id;
    }
    void addTile(TileInfo& info){
        if (info.type >= 3 && info.type <= 27){
            SDL_Rect dst{300*info.posx/size_x, 300*info.posy/size_y, 4, 4};
            SDL_BlitSurface(white_s, nullptr, surface, &dst);
        }
    }
    void updateCar(int32_t id, int32_t x, int32_t y){
        auto& car = cars.at(id);
        car.x = 0.09f*x/size_x;
        car.y = 0.16f*y/size_y + 0.8f;
    }
    void addCar(int32_t id, int32_t x, int32_t y){
        cars.emplace(id, MiniCar{0.09f*x/size_x, 0.16f*y/size_y+0.91f});
    }
    void draw(Camera& camera){
        camera.drawSurface(surface, 0.05, 0.75, 0.09, 0.16);
        for (auto& car : cars)
            camera.drawTexture(RED_DOT, car.second.x+0.05, car.second.y-0.05, 0.5);
    }
    void setSize(int32_t w, int32_t h){
        size_x = w*TILE_TERRAIN_SIZE*METER_TO_PIXEL;
        size_y = h*TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    }
    ~Minimap(){
        SDL_FreeSurface(white_s);
        SDL_FreeSurface(surface);
    }
};


#endif //MICROMACHINES_MINIMAP_H
