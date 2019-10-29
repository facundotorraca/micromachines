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
            car_texture = IMG_LoadTexture(renderer, "assets/sprites/Cars/Car red striped/Car red striped front.png");
            wheel_texture = IMG_LoadTexture(renderer, "assets/sprites/wheel_3.png");

            tile_textures.emplace(3, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_3a.png"));
            tile_textures.emplace(4, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_4a.png"));
            tile_textures.emplace(5, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_5a.png"));
            tile_textures.emplace(8, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_8a.png"));
            tile_textures.emplace(9, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_9a.png"));
            tile_textures.emplace(10, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_10a.png"));
            tile_textures.emplace(13, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_13a.png"));
            tile_textures.emplace(14, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_14a.png"));
            tile_textures.emplace(16, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_16a.png"));
            tile_textures.emplace(27, IMG_LoadTexture(renderer,"assets/sprites/Track/AR_27a.png"));

            tile_textures.emplace(28, IMG_LoadTexture(renderer,"assets/sprites/Track/D_1a.png"));

            tile_textures.emplace(31, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_3a.png"));
            tile_textures.emplace(32, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_4a.png"));
            tile_textures.emplace(33, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_5a.png"));
            tile_textures.emplace(36, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_8a.png"));
            tile_textures.emplace(41, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_13a.png"));
            tile_textures.emplace(42, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_14a.png"));
            tile_textures.emplace(44, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_16a.png"));
            tile_textures.emplace(55, IMG_LoadTexture(renderer,"assets/sprites/Track/DR_27a.png"));
            tile_textures.emplace(59, IMG_LoadTexture(renderer,"assets/sprites/Track/LG_4a.png"));

            tile_textures.emplace(61, IMG_LoadTexture(renderer,"assets/sprites/Track/LS_2a.png"));
            tile_textures.emplace(62, IMG_LoadTexture(renderer,"assets/sprites/Track/LS_3a.png"));
            tile_textures.emplace(63, IMG_LoadTexture(renderer,"assets/sprites/Track/LS_4a.png"));
            tile_textures.emplace(89, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_27a.png"));

            tile_textures.emplace(66, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_3a.png"));
            tile_textures.emplace(67, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_4a.png"));
            tile_textures.emplace(78, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_16a.png"));
            tile_textures.emplace(89, IMG_LoadTexture(renderer,"assets/sprites/Track/SR_27a.png"));

            tile_textures.emplace(90, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/BC_1a.png"));
            tile_textures.emplace(91, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/BC_2a.png"));
            tile_textures.emplace(92, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/BC_3a.png"));
            tile_textures.emplace(93, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/BC_4a.png"));
            tile_textures.emplace(94, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/CC_1a.png"));
            tile_textures.emplace(95, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/CC_2a.png"));
            tile_textures.emplace(96, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/DM_1a.png"));
            tile_textures.emplace(97, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/DM_2a.png"));
            tile_textures.emplace(98, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/GC_1a.png"));
            tile_textures.emplace(99, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/GC_2a.png"));

            tile_textures.emplace(100, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/GC_3a.png"));
            tile_textures.emplace(101, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/GC_4a.png"));

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
            tile_textures.emplace(112, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/tree_small.png"));

            tile_textures.emplace(113, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_1.png"));
            tile_textures.emplace(114, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_2.png"));
            tile_textures.emplace(115, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_3.png"));
            tile_textures.emplace(116, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_4.png"));
            tile_textures.emplace(117, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_5.png"));
            tile_textures.emplace(118, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_6.png"));
            tile_textures.emplace(119, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_7.png"));
            tile_textures.emplace(120, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_8.png"));
            tile_textures.emplace(121, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_9.png"));
            tile_textures.emplace(122, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/TU_10.png"));

            tile_textures.emplace(123, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/YC_1a.png"));
            tile_textures.emplace(124, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/YC_2a.png"));
            tile_textures.emplace(125, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/B_1a.png"));
            tile_textures.emplace(126, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/B_2a.png"));

            tile_textures.emplace(127, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_1a.png"));
            tile_textures.emplace(128, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_2a.png"));
            tile_textures.emplace(129, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_4a.png"));
            tile_textures.emplace(130, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_5a.png"));
            tile_textures.emplace(131, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_6a.png"));
            tile_textures.emplace(132, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/W_3a.png"));
            tile_textures.emplace(133, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/S_1.png"));
            tile_textures.emplace(134, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/S_2.png"));
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
