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

#define MINIMAP_WIDTH 0.12f
#define MINIMAP_HEIGHT 0.213f

struct MiniCar{
    float x;
    float y;
};

class Minimap {
    int32_t my_car_id;
    int32_t size_x;
    int32_t size_y;
    std::map<int32_t, MiniCar>cars;
    SDL_Surface* surface;
    SDL_Surface* white_s;
    SDL_Surface* black_s;
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
        black_s = SDL_CreateRGBSurface(0, 7, 7, 32, 0, 0, 0, 0);
        SDL_FillRect(black_s, nullptr,
                     SDL_MapRGB(white_s->format, 0, 0, 0));
    }
    void setMyID(int32_t id){
        my_car_id = id;
    }
    void addTile(TileInfo& info){
        if ((info.type >= 3 && info.type <= 27) || (info.type >= 29 && info.type <= 32) || (info.type >= 34 && info.type <= 55)){
            SDL_Rect dst_w{300*info.posx/size_x, 300*info.posy/size_y, 4, 4};
            SDL_Rect dst_b{300*info.posx/size_x+10, 300*info.posy/size_y+10, 4, 4};
            SDL_BlitSurface(black_s, nullptr, surface, &dst_b);
            SDL_BlitSurface(white_s, nullptr, surface, &dst_w);
        }
    }
    void updateCar(int32_t id, int32_t x, int32_t y){
        auto& car = cars.at(id);
        car.x = MINIMAP_WIDTH*x/size_x;
        car.y = MINIMAP_HEIGHT*y/size_y + 0.8f;
    }
    void addCar(int32_t id, int32_t x, int32_t y){
        cars.emplace(id, MiniCar{MINIMAP_WIDTH*x/size_x, MINIMAP_HEIGHT*y/size_y+(1-MINIMAP_WIDTH)});
    }
    void draw(Camera& camera){
        camera.drawSurface(surface, 0.05, 0.75, MINIMAP_WIDTH, MINIMAP_HEIGHT);
        for (auto& car : cars)
            camera.drawScreenTexture(RED_DOT, car.second.x + 0.05,
                                     car.second.y - 0.05, 0.5);
    }
    void setSize(int32_t w, int32_t h){
        size_x = w*TILE_TERRAIN_SIZE*METER_TO_PIXEL;
        size_y = h*TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    }
    ~Minimap(){
        SDL_FreeSurface(white_s);
        SDL_FreeSurface(surface);
        SDL_FreeSurface(black_s);
    }
};


#endif //MICROMACHINES_MINIMAP_H
