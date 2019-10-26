
#include <iostream>
#include "Camera.h"

Camera::Camera() :
    posx(0),
    posy(0),
    width(WIDTH_SCREEN),
    height(HEIGHT_SCREEN),
    scale(1),
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
    SDL_GetWindowSize(window, &width, &height);
    scale = (((double)width/1024)+((double)height/720 ))/2;
}

void Camera::drawCar(int32_t x, int32_t y, int32_t rot) {
    copyRender(t_factory.getCarTexture(), x, y, rot,
            CAR_WIDTH*METER_TO_PIXEL, CAR_HEIGHT*METER_TO_PIXEL);
}

void Camera::drawTile(int32_t x, int32_t y, int32_t rot, int32_t type) {
    int32_t wh = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    copyRender(t_factory.getTileTexture(type), x, y, rot, wh, wh);
}

void Camera::drawWheel(int32_t x, int32_t y, int32_t rot) {
    copyRender(t_factory.getWheelTexture(), x, y,
            rot, WIDTH_WHEEL*METER_TO_PIXEL, HEIGHT_WHEEL*METER_TO_PIXEL);
}

void Camera::copyRender(SDL_Texture* tex, int32_t x, int32_t y, int32_t rot, int32_t w, int32_t h){
    int32_t px = (width*0.5) + scale*(x - this->posx);
    int32_t py = (height*0.5) + scale*(y - this->posy);
    SDL_Rect dst{px, py, (int)((double)w*scale), (int)((double)h*scale)};
    if (isInCamera(dst.x, dst.y, dst.w, dst.h)) {
        SDL_RenderCopyEx(renderer, tex, nullptr, &dst,
                         rot,
                         nullptr, SDL_FLIP_NONE);
    }
}

bool Camera::isInCamera(int x,int y, int w, int h){
    return (((x+w)>=0) && (x<width) && ((y+h)>=0) && (y<height));
}

Camera::~Camera() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
