//
// Created by javif on 17/10/2019.
//

#ifndef MICROMACHINES_ENTITY_H
#define MICROMACHINES_ENTITY_H

#include <SDL2/SDL.h>
#include <vector>

class Entity {
protected:
    int posX = 0;
    int posY = 0;
    int rot = 0;
    SDL_Texture* tex = nullptr;
    SDL_Renderer* rend;
public:
    explicit Entity(SDL_Renderer* rend) : rend(rend){};
    virtual void draw(SDL_Point camera) = 0;
    virtual void update(int32_t px, int32_t py, int32_t r) {
        this->posX = px;
        this->posY = py;
        this->rot = r;
    }
    virtual void update(std::vector<int32_t>& update_info) {}
    ~Entity(){
        SDL_DestroyTexture(this->tex);
    }
};


#endif //MICROMACHINES_ENTITY_H
