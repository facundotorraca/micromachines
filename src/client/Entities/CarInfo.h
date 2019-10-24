//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_CARINFO_H
#define MICROMACHINES_CARINFO_H

#include <cstdint>

typedef struct {
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
} CarInfo;

#endif //MICROMACHINES_CARINFO_H
