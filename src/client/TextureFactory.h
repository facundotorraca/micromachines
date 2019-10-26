//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_TEXTUREFACTORY_H
#define MICROMACHINES_TEXTUREFACTORY_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <common/EntityType.h>

class TextureFactory {
    SDL_Texture* car_texture;
    SDL_Texture* wheel_texture;
    std::map<int32_t, SDL_Texture*> tile_textures;
public:
    explicit TextureFactory(SDL_Renderer* renderer){
        if (renderer) {
            car_texture = IMG_LoadTexture(renderer,
                                          "assets/sprites/Cars/Car red striped/Car red striped front.png");
            wheel_texture = IMG_LoadTexture(renderer,
                                            "assets/sprites/wheel_3.png");
            tile_textures.emplace(TYPE_GRASS, IMG_LoadTexture(renderer,
                                                              "assets/sprites/Track/Grass/land_grass04.png"));
            tile_textures.emplace(TYPE_SAND, IMG_LoadTexture(renderer,
                                                             "assets/sprites/Track/Sand/land_sand05.png"));
            tile_textures.emplace(TYPE_ASPHALT, IMG_LoadTexture(renderer,
                                                                "assets/sprites/Track/Asphalt road/road_asphalt22.png"));
            tile_textures.emplace(TYPE_DIRT, IMG_LoadTexture(renderer,
                                                             "assets/sprites/Track/Dirt/land_dirt05.png"));
            tile_textures.emplace(TYPE_ASPHALT_TURN, IMG_LoadTexture(renderer,
                                                                     "assets/sprites/Track/Asphalt road/road_asphalt06.png"));
        }
    }

    TextureFactory& operator=(TextureFactory&& other) noexcept{
        this->car_texture = other.car_texture;
        this->wheel_texture = other.wheel_texture;
        other.car_texture = nullptr;
        other.wheel_texture = nullptr;
        this->tile_textures = std::move(other.tile_textures);
        return *this;
    }

    SDL_Texture *getCarTexture() {
        return car_texture;
    }

    SDL_Texture *getTileTexture(int32_t type) {
        return tile_textures.at(type);
    }

    SDL_Texture *getWheelTexture() {
        return wheel_texture;
    }

    ~TextureFactory(){
        if (car_texture)
            SDL_DestroyTexture(car_texture);
        if (wheel_texture)
            SDL_DestroyTexture(wheel_texture);
        for (auto& tex : tile_textures){
            SDL_DestroyTexture(tex.second);
        }
    }
};

#endif //MICROMACHINES_TEXTUREFACTORY_H
