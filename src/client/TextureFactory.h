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
#define HEALTH_01 5001
#define HEALTH_02 5002
#define HEALTH_03 5003
#define HEALTH_04 5004
#define HEALTH_05 5005
#define HEALTH_06 5006
#define HEALTH_07 5007
#define HEALTH_08 5008
#define HEALTH_09 5009
#define HEALTH_10 5010
#define HEALTH_11 5011
#define HEALTH_12 5012
#define HEALTH_13 5013
#define HEALTH_14 5014
#define HEALTH_15 5015
#define HEALTH_16 5016
#define WHITE_BLOCK 4507
#define RED_DOT 4508



struct Texture{
    SDL_Texture* tex;
    int32_t width;
    int32_t height;
};

class TextureFactory {
    std::map<int32_t, Texture> textures;
    static Texture createTexture(SDL_Renderer* renderer, const char* path){
        SDL_Surface* surface = IMG_Load(path);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
        int w = surface->w, h = surface->h;
        SDL_FreeSurface(surface);
        return {tex, w, h};
    }
    static Texture createTextureWithSize(SDL_Renderer* renderer, const char* path, int w, int h){
        SDL_Texture* tex = IMG_LoadTexture(renderer, path);
        return {tex, w, h};
    }
public:
    explicit TextureFactory(SDL_Renderer* renderer){
        if (renderer) {
            textures.emplace(CAR_TEX, createTextureWithSize(renderer, "assets/sprites/Cars/Car red striped/Car red striped front.png",
                                              CAR_WIDTH*METER_TO_PIXEL, CAR_HEIGHT*METER_TO_PIXEL));
            textures.emplace(DMG_CAR_TEX, createTextureWithSize(renderer, "assets/sprites/Cars/Car red striped/Red striped car crashed.png",
                                                  CAR_WIDTH*METER_TO_PIXEL, CAR_HEIGHT*METER_TO_PIXEL));
            textures.emplace(WHEEL_TEX, createTextureWithSize(renderer, "assets/sprites/wheel_3.png",
                                                WIDTH_WHEEL*METER_TO_PIXEL, HEIGHT_WHEEL*METER_TO_PIXEL));
            textures.emplace(SPEEDOMETER_TEX, createTexture(renderer, "assets/sprites/speedometer.png"));
            textures.emplace(SPEEDOBORDER_TEX, createTexture(renderer, "assets/sprites/UI/Oil bar 2.png"));
            textures.emplace(SPEEDOBAR_TEX, createTexture(renderer, "assets/sprites/UI/Oil bar.png"));
            textures.emplace(LOADING_SCR, createTexture(renderer, "assets/sprites/loading_screen.jpg"));
            textures.emplace(WHITE_BLOCK, createTexture(renderer, "assets/sprites/white_block.png"));
            textures.emplace(RED_DOT, createTexture(renderer, "assets/sprites/red_dot.png"));
            textures.emplace(HEALTH_01, createTexture(renderer, "assets/sprites/HealthBar/100.png"));
            textures.emplace(HEALTH_02, createTexture(renderer, "assets/sprites/HealthBar/92.png"));
            textures.emplace(HEALTH_03, createTexture(renderer, "assets/sprites/HealthBar/85.png"));
            textures.emplace(HEALTH_04, createTexture(renderer, "assets/sprites/HealthBar/78.png"));
            textures.emplace(HEALTH_05, createTexture(renderer, "assets/sprites/HealthBar/71.png"));
            textures.emplace(HEALTH_06, createTexture(renderer, "assets/sprites/HealthBar/64.png"));
            textures.emplace(HEALTH_07, createTexture(renderer, "assets/sprites/HealthBar/57.png"));
            textures.emplace(HEALTH_08, createTexture(renderer, "assets/sprites/HealthBar/50.png"));
            textures.emplace(HEALTH_09, createTexture(renderer, "assets/sprites/HealthBar/43.png"));
            textures.emplace(HEALTH_10, createTexture(renderer, "assets/sprites/HealthBar/37.png"));
            textures.emplace(HEALTH_11, createTexture(renderer, "assets/sprites/HealthBar/30.png"));
            textures.emplace(HEALTH_12, createTexture(renderer, "assets/sprites/HealthBar/24.png"));
            textures.emplace(HEALTH_13, createTexture(renderer, "assets/sprites/HealthBar/18.png"));
            textures.emplace(HEALTH_14, createTexture(renderer, "assets/sprites/HealthBar/12.png"));
            textures.emplace(HEALTH_15, createTexture(renderer, "assets/sprites/HealthBar/6.png"));
            textures.emplace(HEALTH_16, createTexture(renderer, "assets/sprites/HealthBar/0.png"));

            /*-------------------------------ASPHALT_ROADS-----------------------------------------*/
            int tile_width = TILE_TERRAIN_SIZE*METER_TO_PIXEL+5;
            textures.emplace(3, createTextureWithSize(renderer,"assets/sprites/Track/AR_3a.png", tile_width, tile_width)); 
            textures.emplace(4, createTextureWithSize(renderer,"assets/sprites/Track/AR_4a.png", tile_width, tile_width)); 
            textures.emplace(5, createTextureWithSize(renderer,"assets/sprites/Track/AR_5a.png", tile_width, tile_width)); 
            textures.emplace(8, createTextureWithSize(renderer,"assets/sprites/Track/AR_8a.png", tile_width, tile_width)); 
            textures.emplace(9, createTextureWithSize(renderer,"assets/sprites/Track/AR_9a.png", tile_width, tile_width)); 
            textures.emplace(10, createTextureWithSize(renderer,"assets/sprites/Track/AR_10a.png", tile_width, tile_width)); 
            textures.emplace(13, createTextureWithSize(renderer,"assets/sprites/Track/AR_13a.png", tile_width, tile_width)); 
            textures.emplace(14, createTextureWithSize(renderer,"assets/sprites/Track/AR_14a.png", tile_width, tile_width)); 
            textures.emplace(15, createTextureWithSize(renderer,"assets/sprites/Track/AR_15a.png", tile_width, tile_width)); 
            textures.emplace(16, createTextureWithSize(renderer,"assets/sprites/Track/AR_16a.png", tile_width, tile_width)); 
            textures.emplace(17, createTextureWithSize(renderer,"assets/sprites/Track/AR_17a.png", tile_width, tile_width)); 
            textures.emplace(18, createTextureWithSize(renderer,"assets/sprites/Track/AR_18a.png", tile_width, tile_width)); 
            textures.emplace(19, createTextureWithSize(renderer,"assets/sprites/Track/AR_19a.png", tile_width, tile_width)); 
            textures.emplace(21, createTextureWithSize(renderer,"assets/sprites/Track/AR_21a.png", tile_width, tile_width)); 
            textures.emplace(22, createTextureWithSize(renderer,"assets/sprites/Track/AR_22a.png", tile_width, tile_width)); 
            textures.emplace(25, createTextureWithSize(renderer,"assets/sprites/Track/AR_25a.png", tile_width, tile_width)); 
            textures.emplace(27, createTextureWithSize(renderer,"assets/sprites/Track/AR_27a.png", tile_width, tile_width)); 

            /*-----------------------------------DIRT_ROADS----------------------------------------*/
            textures.emplace(28, createTextureWithSize(renderer,"assets/sprites/Track/D_1a.png", tile_width, tile_width)); 
            textures.emplace(31, createTextureWithSize(renderer,"assets/sprites/Track/DR_3a.png", tile_width, tile_width)); 
            textures.emplace(32, createTextureWithSize(renderer,"assets/sprites/Track/DR_4a.png", tile_width, tile_width)); 
            textures.emplace(33, createTextureWithSize(renderer,"assets/sprites/Track/DR_5a.png", tile_width, tile_width)); 
            textures.emplace(36, createTextureWithSize(renderer,"assets/sprites/Track/DR_8a.png", tile_width, tile_width)); 
            textures.emplace(41, createTextureWithSize(renderer,"assets/sprites/Track/DR_13a.png", tile_width, tile_width)); 
            textures.emplace(42, createTextureWithSize(renderer,"assets/sprites/Track/DR_14a.png", tile_width, tile_width)); 
            textures.emplace(44, createTextureWithSize(renderer,"assets/sprites/Track/DR_16a.png", tile_width, tile_width)); 
            textures.emplace(55, createTextureWithSize(renderer,"assets/sprites/Track/DR_27a.png", tile_width, tile_width)); 

            /*-----------------------------------------GRASS---------------------------------------*/
            textures.emplace(56, createTextureWithSize(renderer,"assets/sprites/Track/LG_1a.png", tile_width, tile_width));
            textures.emplace(57, createTextureWithSize(renderer,"assets/sprites/Track/LG_2a.png", tile_width, tile_width));
            textures.emplace(58, createTextureWithSize(renderer,"assets/sprites/Track/LG_3a.png", tile_width, tile_width));
            textures.emplace(59, createTextureWithSize(renderer,"assets/sprites/Track/LG_4a.png", tile_width, tile_width)); 

            /*-----------------------------------SAND_ROADS----------------------------------------*/
            textures.emplace(63, createTextureWithSize(renderer,"assets/sprites/Track/LS_4a.png", tile_width, tile_width)); 
            textures.emplace(66, createTextureWithSize(renderer,"assets/sprites/Track/SR_3a.png", tile_width, tile_width)); 
            textures.emplace(67, createTextureWithSize(renderer,"assets/sprites/Track/SR_4a.png", tile_width, tile_width)); 
            textures.emplace(78, createTextureWithSize(renderer,"assets/sprites/Track/SR_16a.png", tile_width, tile_width)); 
            textures.emplace(89, createTextureWithSize(renderer,"assets/sprites/Track/SR_27a.png", tile_width, tile_width)); 

            /*-----------------------------------TRACK_OBJECTS-------------------------------------*/
            textures.emplace(102, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_1.png", tile_width, tile_width)); 
            textures.emplace(103, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_2.png", tile_width, tile_width)); 
            textures.emplace(104, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_3.png", tile_width, tile_width)); 
            textures.emplace(105, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_4.png", tile_width, tile_width)); 
            textures.emplace(106, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_5.png", tile_width, tile_width)); 
            textures.emplace(107, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_6.png", tile_width, tile_width)); 
            textures.emplace(108, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_7.png", tile_width, tile_width)); 
            textures.emplace(109, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_8.png", tile_width, tile_width)); 
            textures.emplace(110, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_9.png", tile_width, tile_width)); 
            textures.emplace(111, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TD_10.png", tile_width, tile_width)); 

            textures.emplace(112, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TS_1.png", tile_width, tile_width)); 

            textures.emplace(114, createTextureWithSize(renderer,"assets/sprites/TrackObjects/B_1a.png", tile_width, tile_width)); 
            textures.emplace(115, createTextureWithSize(renderer,"assets/sprites/TrackObjects/B_2a.png", tile_width, tile_width)); 
            textures.emplace(116, createTextureWithSize(renderer,"assets/sprites/TrackObjects/W_1a.png", tile_width, tile_width)); 
            textures.emplace(117, createTextureWithSize(renderer,"assets/sprites/TrackObjects/W_2a.png", tile_width, tile_width)); 
            textures.emplace(118, createTextureWithSize(renderer,"assets/sprites/TrackObjects/W_4a.png", tile_width, tile_width)); 
            textures.emplace(119, createTextureWithSize(renderer,"assets/sprites/TrackObjects/W_5a.png", tile_width, tile_width)); 
            textures.emplace(120, createTextureWithSize(renderer,"assets/sprites/TrackObjects/W_6a.png", tile_width, tile_width)); 
            textures.emplace(121, createTextureWithSize(renderer,"assets/sprites/TrackObjects/W_3a.png", tile_width, tile_width)); 

            textures.emplace(122, createTextureWithSize(renderer,"assets/sprites/TrackObjects/S_1.png", tile_width, tile_width)); 
            textures.emplace(123, createTextureWithSize(renderer,"assets/sprites/TrackObjects/S_2.png", tile_width, tile_width)); 

            textures.emplace(124, createTextureWithSize(renderer,"assets/sprites/TrackObjects/TB_1a.png", tile_width, tile_width));
            textures.emplace(125, createTextureWithSize(renderer,"assets/sprites/TrackObjects/trophy_s.png", tile_width, tile_width));
            textures.emplace(126, createTextureWithSize(renderer,"assets/sprites/TrackObjects/trophy_g.png", tile_width, tile_width));
            textures.emplace(127, createTextureWithSize(renderer,"assets/sprites/TrackObjects/trophy_b.png", tile_width, tile_width));


            textures.emplace(128, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PF_1a.png", tile_width, tile_width));
            textures.emplace(129, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PF_2a.png", tile_width, tile_width));
            textures.emplace(130, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PF_3a.png", tile_width, tile_width));
            textures.emplace(131, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PF_4a.png", tile_width, tile_width));
            textures.emplace(132, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PF_5a.png", tile_width, tile_width));

            textures.emplace(133, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PS_1a.png", tile_width, tile_width));
            textures.emplace(134, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PS_2a.png", tile_width, tile_width));
            textures.emplace(135, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PS_3a.png", tile_width, tile_width));
            textures.emplace(136, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PS_4a.png", tile_width, tile_width));
            textures.emplace(137, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PS_5a.png", tile_width, tile_width));
            textures.emplace(138, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PT_1a.png", tile_width, tile_width));
            textures.emplace(139, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PT_2a.png", tile_width, tile_width));
            textures.emplace(140, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PT_3a.png", tile_width, tile_width));
            textures.emplace(141, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PT_4a.png", tile_width, tile_width));
            textures.emplace(142, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PT_5a.png", tile_width, tile_width));

            textures.emplace(143, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PF_1b.png", tile_width, tile_width));
            textures.emplace(144, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PS_1b.png", tile_width, tile_width));
            textures.emplace(145, createTextureWithSize(renderer,"assets/sprites/TrackObjects/PT_1b.png", tile_width, tile_width));
        }
    }

    TextureFactory& operator=(TextureFactory&& other) noexcept{
        this->textures = std::move(other.textures);
        return *this;
    }

    Texture getTexture(int32_t id){
        return textures.at(id);
    }

    ~TextureFactory(){
        for (auto& tex : textures)
            SDL_DestroyTexture(tex.second.tex);
    }
};

#endif //MICROMACHINES_TEXTUREFACTORY_H
