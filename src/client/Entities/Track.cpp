//
// Created by javier on 18/10/19.
//

#include <SDL.h>
#include <SDL_image.h>
#include "Track.h"

void Track::draw(SDL_Point camera) {
    int x = (1280/2) + (posX-camera.x);
    int y = (720/2) + (posY-camera.y);
    SDL_Rect dst{x, y, 1690, 960};
    SDL_RenderCopyEx(rend, tex, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
}

Track::Track(SDL_Renderer *rend, uint8_t map_id) : Entity(rend) {
    this->tex = IMG_LoadTexture(rend, "/home/javier/Facultad/Taller/Micromachines/src/client/Entities/sprites/track.png");
}
