//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_TEXTUREFACTORY_H
#define MICROMACHINES_TEXTUREFACTORY_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <common/EntityType.h>
#include <iostream>

#define CAR_TEX 4500
#define DMG_CAR_TEX 4501
#define WHEEL_TEX 4502
#define SPEEDOMETER_TEX 4503
#define SPEEDOBORDER_TEX 4504
#define SPEEDOBAR_TEX 4505
#define LOADING_SCR 4506

class TextureFactory {
    std::map<int32_t, SDL_Texture*> general_textures;
    std::map<int32_t, SDL_Texture*> tile_textures;
public:
    explicit TextureFactory(SDL_Renderer* renderer){
        if (renderer) {
            general_textures.emplace(CAR_TEX, IMG_LoadTexture(renderer, "assets/sprites/Cars/Car red striped/Car red striped front.png"));
            general_textures.emplace(DMG_CAR_TEX, IMG_LoadTexture(renderer, "assets/sprites/Cars/Car red striped/Red striped car crashed.png"));
            general_textures.emplace(WHEEL_TEX, IMG_LoadTexture(renderer, "assets/sprites/wheel_3.png"));
            general_textures.emplace(SPEEDOMETER_TEX, IMG_LoadTexture(renderer, "assets/sprites/speedometer.png"));
            general_textures.emplace(SPEEDOBORDER_TEX, IMG_LoadTexture(renderer, "assets/sprites/UI/Oil bar 2.png"));
            general_textures.emplace(SPEEDOBAR_TEX, IMG_LoadTexture(renderer, "assets/sprites/UI/Oil bar.png"));
            general_textures.emplace(LOADING_SCR, IMG_LoadTexture(renderer, "assets/sprites/loading_screen.jpg"));

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

            /*-----------------------------------------Podium-------------------------------------------------*/
            tile_textures.emplace(125, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/trophy_s.png"));
            tile_textures.emplace(126, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/trophy_g.png"));
            tile_textures.emplace(127, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/trophy_b.png"));


            tile_textures.emplace(128, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PF_1a.png"));
            tile_textures.emplace(129, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PF_2a.png"));
            tile_textures.emplace(130, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PF_3a.png"));
            tile_textures.emplace(131, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PF_4a.png"));
            tile_textures.emplace(132, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PF_5a.png"));

            tile_textures.emplace(133, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PS_1a.png"));
            tile_textures.emplace(134, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PS_2a.png"));
            tile_textures.emplace(135, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PS_3a.png"));
            tile_textures.emplace(136, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PS_4a.png"));
            tile_textures.emplace(137, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PS_5a.png"));
            tile_textures.emplace(138, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PT_1a.png"));
            tile_textures.emplace(139, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PT_2a.png"));
            tile_textures.emplace(140, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PT_3a.png"));
            tile_textures.emplace(141, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PT_4a.png"));
            tile_textures.emplace(142, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PT_5a.png"));

            tile_textures.emplace(143, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PF_1b.png"));
            tile_textures.emplace(144, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PS_1b.png"));
            tile_textures.emplace(145, IMG_LoadTexture(renderer,"assets/sprites/TrackObjects/PT_1b.png"));
        }
    }

    TextureFactory& operator=(TextureFactory&& other) noexcept{
        this->general_textures = std::move(other.general_textures);
        this->tile_textures = std::move(other.tile_textures);
        return *this;
    }

    SDL_Texture *getCarTexture() {
        return general_textures.at(CAR_TEX);
    }

    SDL_Texture *getTileTexture(int32_t type) {
        try {
            return tile_textures.at(type);
        } catch (std::out_of_range& e){
            std::cerr << "Texture " << type << " not found" << std::endl;
            return nullptr;
        }
    }

    SDL_Texture *getWheelTexture() {
        return general_textures.at(WHEEL_TEX);
    }

    SDL_Texture* getSpeedometer(){
        return general_textures.at(SPEEDOMETER_TEX);
    }

    SDL_Texture *getDamagedCarTexture() {
        return general_textures.at(DMG_CAR_TEX);
    }

    SDL_Texture* getHealthBarTexture(){
        return general_textures.at(SPEEDOBORDER_TEX);
    }

    SDL_Texture* getHealthTexture(){
        return general_textures.at(SPEEDOBAR_TEX);
    }
    ~TextureFactory(){
        for (auto& tex : general_textures)
            SDL_DestroyTexture(tex.second);
        for (auto& tex : tile_textures)
            SDL_DestroyTexture(tex.second);
    }


    SDL_Texture *getLoadingTexture() {
        return general_textures.at(LOADING_SCR);
    }
};

#endif //MICROMACHINES_TEXTUREFACTORY_H
