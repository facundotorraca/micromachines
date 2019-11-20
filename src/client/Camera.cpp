
#include <iostream>
#include "Camera.h"
#include <cmath>
#include <iomanip>

#define DEG2RAD 0.01745329252
#define CAM_DEAD_ZONE 0
#define CAMERA_DISTANCE 0.0018
#define FORWARD_VIEW 5
#define CAM_DELAY 90

Camera::Camera() :
    posx(0),
    posy(0),
    width(WIDTH_SCREEN),
    height(HEIGHT_SCREEN),
    window_scale(0.5f*(((float)height/1080)+((float)width/1920))),
    draw_scale(1),
    t_factory(nullptr),
    t_drawer(nullptr),
    renderer(nullptr),
    window(nullptr),
    recording(false)
{
    /*window = SDL_CreateWindow("Micromachines", 0, 0, width, height,
            SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);
    */
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    t_factory = std::move(TextureFactory(renderer));
    t_drawer = std::move(TextDrawer(renderer));
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

float f(float x){
    if (x<=CAM_DEAD_ZONE)
        return exp(x-CAM_DEAD_ZONE);
    return x-CAM_DEAD_ZONE+1;
}

std::tuple<float, float> mean(std::list<CarData>& points){
    if (points.size() <= 1){
        return {0, 0};
    }
    float sum_vel = 0;
    float sum_rot = 0;
    for (auto& point : points){
        sum_vel += point.vel;
        sum_rot += point.rot;
    }
    return {sum_vel/(points.size()-1.0), sum_rot/(points.size()-1.0)};
}

void Camera::update(int32_t posx, int32_t posy, int32_t carvel, int32_t rot) {
    float rad = DEG2RAD*rot;
    if (hypot(posx-car_pos.back().x, posy-car_pos.back().y) > 200)
        car_pos.clear();
    car_pos.emplace_back(CarData{posx, posy, carvel, rad});
    auto means = mean(car_pos);
    float vel = std::get<0>(means)*3.6/METER_TO_PIXEL;
    float prom_rot = std::get<1>(means);
    float factor = f(vel);
    draw_scale = 1/((factor*CAMERA_DISTANCE)+1)*window_scale;
    this->posx = (float)posx - (draw_scale*sin(prom_rot)*factor*FORWARD_VIEW);
    this->posy = (float)posy + (draw_scale*cos(prom_rot)*factor*FORWARD_VIEW*((float)height/width));
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
        if (this->isRecording())
            this->stopRecording();
        width = w;
        height = h;
        window_scale = (((float) width / 1920) + ((float) height / 1080)) / 2;
    }
}

void Camera::copyRender(SDL_Texture* tex, int32_t x, int32_t y, int32_t rot, int32_t w, int32_t h){
    SDL_Rect dst{x, y, w, h};
    SDL_RenderCopyEx(renderer, tex, nullptr, &dst, rot,
                         nullptr, SDL_FLIP_NONE);
}

bool Camera::isInCamera(int x,int y, int w, int h){
    return (((x+w)>=0) && (x<width) && ((y+h)>=0) && (y<height));
}

Camera::~Camera() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Camera::drawWorldTexture(int32_t id, int32_t px, int32_t py, int32_t sizex,
                         int32_t sizey, int32_t rot) {
    Texture tex = t_factory.getTexture(id);
    int32_t draw_x = (0.5f*width) - draw_scale*(posx-px);
    int32_t draw_y = (0.5f*height) - draw_scale*(posy-py);
    if (isInCamera(draw_x, draw_y, sizex*draw_scale, sizey*draw_scale)){
        copyRender(tex.tex, draw_x, draw_y, rot, sizex*draw_scale, sizey*draw_scale);
    }
}

void Camera::drawExternalWorldTexture(SDL_Texture* texture, int32_t px, int32_t py,
                              int32_t sizex, int32_t sizey, int32_t rot, bool force) {
    int32_t draw_x = (0.5f*width) - draw_scale*(posx-px);
    int32_t draw_y = (0.5f*height) - draw_scale*(posy-py);
    if (isInCamera(draw_x, draw_y, sizex*draw_scale, sizey*draw_scale) || force){
        copyRender(texture, draw_x, draw_y, rot, sizex*draw_scale, sizey*draw_scale);
    }
}

void Camera::drawScreenTexture(int32_t id, float posx, float posy, float sizex, float sizey) {
    Texture tex = t_factory.getTexture(id);
    int x = posx*width;
    int y = posy*height;
    int w = (sizex*width);
    int h = (sizey*height);
    copyRender(tex.tex, x, y, 0, w, h);
}

void Camera::drawScreenTexture(int32_t id, float posx, float posy, float scale) {
    Texture tex = t_factory.getTexture(id);
    int x = posx*width;
    int y = posy*height;
    int w = tex.width*window_scale*scale;
    int h = tex.height*window_scale*scale;
    copyRender(tex.tex, x, y, 0, w, h);
}

void Camera::drawSurface(SDL_Surface* surface, float posx, float posy, float w_surface, float h_surface){
    SDL_Texture* texture =  SDL_CreateTextureFromSurface(renderer, surface);
    int x = posx*width;
    int y = posy*height;
    int w = w_surface*width;
    int h = h_surface*height;
    copyRender(texture, x, y, 0, w, h);
    SDL_DestroyTexture(texture);
}

void Camera::drawText(const std::string &text, float posx, float posy,
                      float size, size_t padding) {
    int x = posx*width;
    int y = posy*height;
    int h = 60*size*window_scale;
    t_drawer.drawText(text, x, y, h, 5*window_scale, padding);
}

void Camera::drawFullScreenTexture(int32_t id) {
    Texture tex = t_factory.getTexture(id);
    copyRender(tex.tex, 0, 0, 0, width, height);
}

bool Camera::isRecording() {
    return recorder.isRecording();
}

void Camera::startRecording() {
    recorder.startRecording(renderer, width, height);
}

void Camera::stopRecording() {
    recorder.stopRecording();
}

void Camera::setRecordingTarget() {
    SDL_SetRenderTarget(renderer, recorder.getRecordingTexture());
}

void Camera::setDefaultTarget() {
    SDL_SetRenderTarget(renderer, nullptr);
}

void Camera::sendToRecorder() {
    recorder.recordFrame(renderer);
}

void Camera::drawRecordingTexture() {
    drawFullScreenTexture(RECORDING_TEX);
}

Texture Camera::getTexture(int32_t id) {
    return t_factory.getTexture(id);
}

SDL_Texture *Camera::createTexture(SDL_Surface *texture) {
    return SDL_CreateTextureFromSurface(renderer, texture);
}
