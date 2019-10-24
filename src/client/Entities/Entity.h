#ifndef MICROMACHINES_ENTITY_H
#define MICROMACHINES_ENTITY_H

#include <vector>
#include <SDL2/SDL.h>

class Entity {
    protected:
        int posX = 0;
        int posY = 0;
        int rot = 0;
        SDL_Texture* tex = nullptr;
        SDL_Renderer* rend;
    public:
        explicit Entity(SDL_Renderer* rend):
            rend(rend)
        {};

        virtual void draw(SDL_Point camera, int32_t width, int32_t height)const = 0;
        virtual void update_position(int32_t px, int32_t py, int32_t r) {
            this->posX = px;
            this->posY = py;
            this->rot = r;
        }
        ~Entity(){
            SDL_DestroyTexture(this->tex);
        }
};


#endif //MICROMACHINES_ENTITY_H
