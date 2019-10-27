
#include <iostream>
#include "Camera.h"
#include <cmath>
Camera::Camera() :
    posx(0),
    posy(0),
    width(WIDTH_SCREEN),
    height(HEIGHT_SCREEN),
    window_scale(1),
    draw_scale(1),
    t_factory(nullptr),
    renderer(nullptr),
    window(nullptr)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Micromachines", 0, 0, width, height, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    t_factory = std::move(TextureFactory(renderer));
    for (int i = 1; i < 5; i++) {
        car_pos.emplace_back(SDL_Point{0, 0});
    }
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

double f(double x){
    if (x<=CAM_DEAD_ZONE)
        return exp(x-CAM_DEAD_ZONE);
    return x-CAM_DEAD_ZONE+1;
}

void Camera::update(int32_t posx, int32_t posy, int32_t rot) {
    car_pos.emplace_back(SDL_Point{posx, posy});
    double rad = DEG2RAD*rot;
    double dx = car_pos.back().x - car_pos.front().x;
    double dy = car_pos.back().y - car_pos.front().y;
    double vel = hypot(dx, dy);
    double factor = f(vel);
    draw_scale = 1/((factor/CAMERA_DISTANCE)+1)*window_scale;
    this->posx = (double)posx - (draw_scale*sin(rad)*factor*FORWARD_VIEW);
    this->posy = (double)posy + (draw_scale*cos(rad)*factor*FORWARD_VIEW*(height/width));
    car_pos.erase(car_pos.begin());
}

void Camera::draw() {
    SDL_RenderPresent(renderer);
}

void Camera::clear() {
    SDL_RenderClear(renderer);
    int32_t w, h;
    SDL_GetWindowSize(window, &w, &h);
    if (!(w==width && h==height)) {
        width = w;
        height = h;
        window_scale = (((double) width / 1920) + ((double) height / 1080)) / 2;
    }
}

void Camera::drawCar(int32_t x, int32_t y, int32_t rot) {
    copyRender(t_factory.getCarTexture(), x, y, rot,
            CAR_WIDTH*METER_TO_PIXEL, CAR_HEIGHT*METER_TO_PIXEL);
}

void Camera::drawTile(int32_t x, int32_t y, int32_t rot, int32_t type) {
    int32_t wh = TILE_TERRAIN_SIZE*METER_TO_PIXEL+3;
    copyRender(t_factory.getTileTexture(type), x, y, rot, wh, wh);
}

void Camera::drawWheel(int32_t x, int32_t y, int32_t rot) {
    copyRender(t_factory.getWheelTexture(), x, y,
            rot, WIDTH_WHEEL*METER_TO_PIXEL, HEIGHT_WHEEL*METER_TO_PIXEL);
}

void Camera::copyRender(SDL_Texture* tex, int32_t x, int32_t y, int32_t rot, int32_t w, int32_t h){
    int32_t px = (0.5f*width) - draw_scale*(posx-x);
    int32_t py = (0.5f*height) - draw_scale*(posy-y);
    SDL_Rect dst{px, py, (int)(draw_scale*w), (int)(draw_scale*h)};
    if (isInCamera(dst.x, dst.y, dst.w, dst.h)) {
        SDL_RenderCopyEx(renderer, tex, nullptr, &dst, rot,
                         nullptr, SDL_FLIP_NONE);
    }
}

bool Camera::isInCamera(int x,int y, int w, int h){
    return (((x+w)>=0) && (x<width) && ((y+h)>=0) && (y<height));
}

Camera::~Camera() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
