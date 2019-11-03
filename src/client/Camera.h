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
    double rot;
};

class Camera {
    double posx;
    double posy;
    std::list<CarData> car_pos;
    int32_t width;
    int32_t height;
    double window_scale;
    double draw_scale;
    TextureFactory t_factory;
    TextDrawer t_drawer;
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
    void drawWorldTexture(int32_t id, int32_t posx, int32_t posy, int32_t rot);
    void drawTexture(int32_t id, double posx, double posy, double scale);
    void drawText(const std::string& text, double posx, double posy, double size, size_t padding);
    void drawFullScreenTexture(int32_t id);
    ~Camera();

};


#endif //MICROMACHINES_CAMERA_H
