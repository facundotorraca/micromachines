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
#include "TextDrawer.h"

struct CarData{
    int32_t x;
    int32_t y;
    int32_t vel;
    float rot;
};

class Camera {
    float posx;
    float posy;
    std::list<CarData> car_pos;
    int32_t width;
    int32_t height;
    float window_scale;
    float draw_scale;
    TextureFactory t_factory;
    TextDrawer t_drawer;
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool isInCamera(int x, int y, int w, int h);
    void copyRender(SDL_Texture* tex, int32_t x, int32_t y, int32_t rot,
            int32_t w, int32_t h);
public:
    Camera();
    void update(int32_t posx, int32_t posy, int32_t carvel, int32_t rot);
    void draw();
    void clear();

    void drawWorldTexture(int32_t id, int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, int32_t rot);
    void drawScreenTexture(int32_t id, float posx, float posy, float scale);
    void drawScreenTexture(int32_t id, float posx, float posy, float sizex, float sizey);
    void drawSurface(SDL_Surface* surface, float posx, float posy, float width, float height);
    void drawText(const std::string& text, float posx, float posy, float size, size_t padding);
    void drawFullScreenTexture(int32_t id);
    ~Camera();

};


#endif //MICROMACHINES_CAMERA_H
