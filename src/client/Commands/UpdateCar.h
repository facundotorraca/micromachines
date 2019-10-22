//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_UPDATECAR_H
#define MICROMACHINES_UPDATECAR_H


#include "Command.h"

class UpdateCar : public Command{
    int32_t car_id;
    int32_t carx;
    int32_t cary;
    int32_t carrot;
    int32_t w1x;
    int32_t w1y;
    int32_t w1rot;
    int32_t w2x;
    int32_t w2y;
    int32_t w2rot;
    int32_t w3x;
    int32_t w3y;
    int32_t w3rot;
    int32_t w4x;
    int32_t w4y;
    int32_t w4rot;

public:
    UpdateCar(int32_t car_id,
              int32_t carx,
              int32_t cary,
              int32_t carrot,
              int32_t w1x,
              int32_t w1y,
              int32_t w1rot,
              int32_t w2x,
              int32_t w2y,
              int32_t w2rot,
              int32_t w3x,
              int32_t w3y,
              int32_t w3rot,
              int32_t w4x,
              int32_t w4y,
              int32_t w4rot) :
              car_id(car_id),
              carx(carx),
              cary(cary),
              carrot(carrot),
              w1x(w1x),
              w1y(w1y),
              w1rot(w1rot),
              w2x(w2x),
              w2y(w2y),
              w2rot(w2rot),
              w3x(w3x),
              w3y(w3y),
              w3rot(w3rot),
              w4x(w4x),
              w4y(w4y),
              w4rot(w4rot) {}

    void apply(Camera& camera) override {
        camera.updateCar(car_id,
                carx,
                cary,
                carrot,
                w1x,
                w1y,
                w1rot,
                w2x,
                w2y,
                w2rot,
                w3x,
                w3y,
                w3rot,
                w4x,
                w4y,
                w4rot);
    }
};


#endif //MICROMACHINES_UPDATECAR_H
