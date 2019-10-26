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
    double posx;
    double posy;
    std::list<SDL_Point> car_pos;
    int32_t width;
    int32_t height;
    double scale;
    TextureFactory t_factory;
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool isInCamera(int x, int y, int w, int h);
    void copyRender(SDL_Texture* tex, int32_t x, int32_t y, int32_t rot,
            int32_t w, int32_t h);
public:
    Camera();
    void update(int32_t posx, int32_t posy, int32_t rot);
    void draw();
    void clear();
    void drawCar(int32_t posx, int32_t posy, int32_t rot);
    void drawTile(int32_t posx, int32_t posy, int32_t rot, int32_t type);
    void drawWheel(int32_t posx, int32_t posy, int32_t rot);
    ~Camera();
};


#endif //MICROMACHINES_CAMERA_H
