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
#include <client/Entities/CarInfo.h>

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

        void updateCar(CarInfo info);

        void setRenderer(SDL_Renderer *pRenderer);
};


#endif //MICROMACHINES_CAMERA_H
