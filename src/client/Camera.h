//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include <list>
#include <map>
#include <mutex>
#include <SDL2/SDL.h>
#include <common/Sizes.h>
#include "TextureFactory.h"

class Camera {
    int32_t posx;
    int32_t posy;
    int32_t width;
    int32_t height;
    TextureFactory t_factory;
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool isInCamera(int x, int y, int w, int h);
public:
    Camera();
    void update(int32_t posx, int32_t posy);
    void draw();
    void clear();
    void drawCar(int32_t posx, int32_t posy, int32_t rot);
    void drawTile(int32_t posx, int32_t posy, int32_t rot);
    void drawWheel(int32_t posx, int32_t posy, int32_t rot);
};


#endif //MICROMACHINES_CAMERA_H
