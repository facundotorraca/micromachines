//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_TEXTUREFACTORY_H
#define MICROMACHINES_TEXTUREFACTORY_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <common/EntityType.h>
#include <iostream>

class TextureFactory {
    SDL_Texture* car_texture;
    SDL_Texture* wheel_texture;
    std::map<int32_t, SDL_Texture*> tile_textures;
public:
    explicit TextureFactory(SDL_Renderer* renderer){
        if (renderer) {
            car_texture = IMG_LoadTexture(renderer, "assets/sprites/Cars/Car red striped/Car red striped front.png");
            wheel_texture = IMG_LoadTexture(renderer, "assets/sprites/wheel_3.png");

            /*-------------------------------ASPHALT_ROADS-----------------------------------------*/
            tile_textures.emplace(3, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_3a.png"));
            tile_textures.emplace(4, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_4a.png"));
            tile_textures.emplace(5, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_5a.png"));
            tile_textures.emplace(8, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_8a.png"));
            tile_textures.emplace(9, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_9a.png"));
            tile_textures.emplace(10, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_10a.png"));
            tile_textures.emplace(13, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_13a.png"));
            tile_textures.emplace(14, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_14a.png"));
            tile_textures.emplace(15, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_15a.png"));
            tile_textures.emplace(16, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_16a.png"));
            tile_textures.emplace(17, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_17a.png"));
            tile_textures.emplace(18, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_18a.png"));
            tile_textures.emplace(19, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_19a.png"));
            tile_textures.emplace(21, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_21a.png"));
            tile_textures.emplace(22, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_22a.png"));
            tile_textures.emplace(25, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_25a.png"));
            tile_textures.emplace(27, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_27a.png"));

            /*-----------------------------------DIRT_ROADS----------------------------------------*/
            tile_textures.emplace(28, IMG_LoadTexture(renderer,"assets/sprites/Track/D_1a.png"));
            tile_textures.emplace(31, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_3a.png"));
            tile_textures.emplace(32, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_4a.png"));
            tile_textures.emplace(33, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_5a.png"));
            tile_textures.emplace(36, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_8a.png"));
            tile_textures.emplace(41, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_13a.png"));
            tile_textures.emplace(42, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_14a.png"));
            tile_textures.emplace(44, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_16a.png"));
            tile_textures.emplace(55, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_27a.png"));

            /*-----------------------------------------GRASS---------------------------------------*/
            tile_textures.emplace(59, IMG_LoadTexture(renderer,"assets/sprites/Track/LG_4a.png"));

            /*-----------------------------------SAND_ROADS----------------------------------------*/
            tile_textures.emplace(63, IMG_LoadTexture(renderer,"assets/sprites/Track/LS_4a.png"));
            tile_textures.emplace(66, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_3a.png"));
            tile_textures.emplace(67, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_4a.png"));
            tile_textures.emplace(78, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_16a.png"));
            tile_textures.emplace(89, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_27a.png"));

            /*-----------------------------------TRACK_OBJECTS-------------------------------------*/
            tile_textures.emplace(102, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_1.png"));
            tile_textures.emplace(103, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_2.png"));
            tile_textures.emplace(104, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_3.png"));
            tile_textures.emplace(105, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_4.png"));
            tile_textures.emplace(106, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_5.png"));
            tile_textures.emplace(107, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_6.png"));
            tile_textures.emplace(108, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_7.png"));
            tile_textures.emplace(109, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_8.png"));
            tile_textures.emplace(110, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_9.png"));
            tile_textures.emplace(111, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TD_10.png"));

            tile_textures.emplace(112, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TS_1.png"));

            tile_textures.emplace(114, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/B_1a.png"));
            tile_textures.emplace(115, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/B_2a.png"));
            tile_textures.emplace(116, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_1a.png"));
            tile_textures.emplace(117, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_2a.png"));
            tile_textures.emplace(118, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_4a.png"));
            tile_textures.emplace(119, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_5a.png"));
            tile_textures.emplace(120, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_6a.png"));
            tile_textures.emplace(121, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_3a.png"));

            tile_textures.emplace(122, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/S_1.png"));
            tile_textures.emplace(123, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/S_2.png"));

            tile_textures.emplace(124, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TB_1a.png"));
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
        try {
            return tile_textures.at(type);
        } catch (std::out_of_range& e){
            std::cerr << "Texture not found" << std::endl;
            return nullptr;
        }
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
