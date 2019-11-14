#ifndef MICROMACHINES_DTO_INFO_H
#define MICROMACHINES_DTO_INFO_H

#include <cstdint>
#include <common/Sizes.h>
#include <model/Vehicle/CarSpecs.h>

typedef enum {
    MUD,
    OIL,
    FIX,
    ROCK,
    BOOST,
    NO_MODIFIER
} modifier_t;

typedef struct {
    int32_t max_life;
    int32_t current_life;
} DTO_CarLife;

typedef struct {
    int32_t ID;
    int32_t laps;
    CarSpecs specs;
    DTO_CarLife life;
    int32_t position;
    modifier_t modifier;
} DTO_Car;

typedef struct {
    int32_t cars;
    int32_t total_laps;
    DTO_Car car_info[MAX_PLAYERS];
} DTO_Info;

#endif //MICROMACHINES_DTO_INFO_H
