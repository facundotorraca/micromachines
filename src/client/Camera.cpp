
#include <iostream>
#include "Camera.h"
#include <cmath>
#include <iomanip>

#define DEG2RAD 0.01745329252
#define CAM_DEAD_ZONE 0
#define CAMERA_DISTANCE 0.013
#define FORWARD_VIEW 30
#define CAM_DELAY 90

Camera::Camera() :
    posx(0),
    posy(0),
    width(WIDTH_SCREEN),
    height(HEIGHT_SCREEN),
    window_scale(0.5f*(((double)height/1080)+((double)width/1920))),
    draw_scale(1),
    t_factory(nullptr),
    t_drawer(nullptr),
    renderer(nullptr),
    window(nullptr)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Micromachines", 0, 0, width, height,
            SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    t_factory = std::move(TextureFactory(renderer));
    t_drawer = std::move(TextDrawer(renderer));
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

double f(double x){
    if (x<=CAM_DEAD_ZONE)
        return exp(x-CAM_DEAD_ZONE);
    return x-CAM_DEAD_ZONE+1;
}

std::tuple<double, double, double> mean(std::list<CarData>& points){
    if (points.size() <= 1){
        return {0, 0, 0};
    }

    double sum_x = 0;
    double sum_y = 0;
    double sum_rot = 0;
    auto iter = points.begin();
    int prev_x = iter->x;
    int prev_y = iter->y;
    iter++;
    for (;iter != points.end(); iter++){
        sum_x += (iter->x - prev_x);
        sum_y += (iter->y - prev_y);
        sum_rot += iter->rot;
        prev_x = iter->x;
        prev_y = iter->y;
    }
    return {sum_x/(points.size()-1.0), sum_y/(points.size()-1.0), sum_rot/(points.size()-1.0)};
}

void Camera::update(int32_t posx, int32_t posy, int32_t rot) {
    double rad = DEG2RAD*rot;
    car_pos.emplace_back(CarData{posx, posy, rad});
    auto means = mean(car_pos);
    double dx = std::get<0>(means);
    double dy = std::get<1>(means);
    double prom_rot = std::get<2>(means);
    double vel = hypot(dx, dy);
    double factor = f(vel);
    draw_scale = 1/((factor*CAMERA_DISTANCE)+1)*window_scale;
    this->posx = (double)posx - (draw_scale*sin(prom_rot)*factor*FORWARD_VIEW);
    this->posy = (double)posy + (draw_scale*cos(prom_rot)*factor*FORWARD_VIEW*((double)height/width));
    if (car_pos.size() >= CAM_DELAY)
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

void Camera::drawDamagedCar(int32_t posx, int32_t posy, int32_t rot) {
    copyRender(t_factory.getDamagedCarTexture(),posx , posy, rot,
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
    //TTF_Quit();
    SDL_Quit();
}

void Camera::drawBackground(int32_t type, int32_t width, int32_t height) {
    int32_t tile_width = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            copyRender(t_factory.getTileTexture(type),
                    tile_width*i, tile_width*j, 0,
                    tile_width + 5, tile_width + 5);
        }
    }
}

void Camera::drawSpeedometer(int32_t p_speed) {
    int speed = p_speed/METER_TO_PIXEL;
    int x = width-(500*window_scale);
    int y = 60*window_scale;
    int h = 60*window_scale;
    int w = h*1.1212121;

    SDL_Texture* speedo = t_factory.getSpeedometer();
    std::string text = std::to_string(speed)+" km/h";
    SDL_Rect dst{x, y, w, h};
    SDL_RenderCopy(renderer, speedo, nullptr, &dst);
    t_drawer.drawText(text, width-(420*window_scale), w, w*0.7, 5*window_scale, 7);
}

void Camera::drawHealthBar(int32_t health) {

}

