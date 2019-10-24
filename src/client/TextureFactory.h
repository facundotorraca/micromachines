//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_TEXTUREFACTORY_H
#define MICROMACHINES_TEXTUREFACTORY_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define CAR 70
#define TILE 71
#define WHEEL 72

class TextureFactory {
    std::map<int32_t, SDL_Texture*> textures;
public:
    explicit TextureFactory(SDL_Renderer* renderer){
        textures.emplace(CAR, IMG_LoadTexture(renderer, "assets/sprites/Cars/Car red striped/Car red striped front.png"));
        textures.emplace(WHEEL, IMG_LoadTexture(renderer, "assets/sprites/wheel_3.png"));
        textures.emplace(TILE, IMG_LoadTexture(renderer, "assets/sprites/Track/Grass/land_grass04.png"));
    }

    SDL_Texture *getCarTexture() {
        return textures.at(CAR);
    }

    SDL_Texture *getTileTexture() {
        return textures.at(TILE);
    }

    SDL_Texture *getWheelTexture() {
        return textures.at(WHEEL);
    }
};

#endif //MICROMACHINES_TEXTUREFACTORY_H
