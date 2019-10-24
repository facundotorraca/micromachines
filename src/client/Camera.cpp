
#include <iostream>
#include "Camera.h"

Camera::Camera() :
    posx(0),
    posy(0),
    width(WIDTH_SCREEN),
    height(HEIGHT_SCREEN),
    t_factory(nullptr),
    renderer(nullptr),
    window(nullptr)
{
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    t_factory = TextureFactory(renderer);
}

void Camera::update(int32_t posx, int32_t posy) {
    this->posx = posx;
    this->posy = posy;
}

void Camera::draw() {
    SDL_RenderPresent(renderer);
}

void Camera::clear() {
    SDL_RenderClear(renderer);
}

void Camera::drawCar(int32_t x, int32_t y, int32_t rot) {
    int32_t px = (width / 2) + x - this->posx;
    int32_t py = (height / 2) + y - this->posy;
    SDL_Rect dst{px, py, (int) (CAR_WIDTH * METER_TO_PIXEL),
                     (int) (CAR_HEIGHT * METER_TO_PIXEL)};
    if (isInCamera(px, py, dst.w, dst.h)) {
        SDL_RenderCopyEx(renderer, t_factory.getCarTexture(), nullptr, &dst,
                         rot,
                         nullptr, SDL_FLIP_NONE);
    }
}

void Camera::drawTile(int32_t x, int32_t y, int32_t rot) {
    int32_t px = (width/2) + x - this->posx;
    int32_t py = (height/2) + y - this->posy;
    SDL_Rect dst{px, py, (int) (WIDTH_TILE * METER_TO_PIXEL),
                     (int) (HEIGHT_TILE * METER_TO_PIXEL)};
    if (isInCamera(px, py, dst.w, dst.h)) {
        SDL_RenderCopyEx(renderer, t_factory.getTileTexture(), nullptr, &dst,
                         rot,
                         nullptr, SDL_FLIP_NONE);
    }
}

void Camera::drawWheel(int32_t x, int32_t y, int32_t rot) {
    int32_t px = (width/2) + x - this->posx;
    int32_t py = (height/2) + y - this->posy;
    SDL_Rect dst{px, py, (int) (WIDTH_WHEEL * METER_TO_PIXEL),
                     (int) (HEIGHT_WHEEL * METER_TO_PIXEL)};
    if (isInCamera(px, py, dst.w, dst.h)) {
        SDL_RenderCopyEx(renderer, t_factory.getWheelTexture(), nullptr, &dst,
                         rot,
                         nullptr, SDL_FLIP_NONE);
    }
}

bool Camera::isInCamera(int x,int y, int w, int h){
    return true;//(((x+w)>=0) && (x<width) && ((y+h)>=0) && (y<height));
}