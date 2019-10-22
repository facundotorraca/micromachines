//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include <list>
#include <map>
#include <mutex>
#include <client/Entities/Entity.h>
#include <SDL2/SDL.h>
#include <memory>
#include <client/Entities/Car.h>

class Camera {
    SDL_Renderer* rend;

    std::list<std::unique_ptr<Entity>> background;
    std::map<uint8_t, Car> cars;
    std::mutex mtx;

    SDL_Point camera;

    int32_t width;
    int32_t height;
    int32_t my_car_ID;

    public:
        Camera(SDL_Renderer* rend, int32_t x, int32_t y);

        void draw();

        void setOwnID(int32_t id);

        void setTrack(int32_t id);

        void updateCar(int32_t car_id,
                       int32_t carx, int32_t cary, int32_t carrot,
                       int32_t w1x, int32_t w1y, int32_t w1rot,
                       int32_t w2x, int32_t w2y, int32_t w2rot,
                       int32_t w3x, int32_t w3y, int32_t w3rot,
                       int32_t w4x, int32_t w4y, int32_t w4rot);

        void setRenderer(SDL_Renderer *pRenderer);
};


#endif //MICROMACHINES_CAMERA_H
