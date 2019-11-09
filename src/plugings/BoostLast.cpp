//
// Created by alejo on 7/11/19.
//

#include <model/DTO_Info.h>
#include <iostream>

#define IMPULSE_MODIFIER 1.5
#define FORCE_MODIFIER 1.5

typedef struct self {
    uint32_t step;
    int32_t last_boosted_id;
} BoostLast_t;

void modify_specs(CarSpecs *specs) {
    specs->front_wheel_max_force = specs->front_wheel_max_force * FORCE_MODIFIER;
    specs->back_wheel_max_force = specs->back_wheel_max_force * FORCE_MODIFIER;
    specs->back_max_lateral_impulse = specs->back_max_lateral_impulse * IMPULSE_MODIFIER;
    specs->front_max_lateral_impulse = specs->front_max_lateral_impulse * IMPULSE_MODIFIER;
}

void reset_specs(CarSpecs *specs) {
    specs->front_wheel_max_force = specs->front_wheel_max_force / FORCE_MODIFIER;
    specs->back_wheel_max_force = specs->back_wheel_max_force / FORCE_MODIFIER;
    specs->back_max_lateral_impulse = specs->back_max_lateral_impulse / IMPULSE_MODIFIER;
    specs->front_max_lateral_impulse = specs->front_max_lateral_impulse / IMPULSE_MODIFIER;
}

void run(BoostLast_t *self, DTO_Info *params) {
    size_t last = 0;
    int32_t last_id = -1;
    CarSpecs *last_specs = nullptr;
    if(self->step % 50 != 0) {
        self->step++;
        return;
    }
    for (size_t ind = 0; ind < params->cars; ind++) {
        if (params->car_info[ind].position > last) {
            last = params->car_info[ind].position;
            last_specs = &(params->car_info[ind].specs);
            last_id = params->car_info[ind].ID;
        }
        if (params->car_info[ind].ID == self->last_boosted_id) {
            reset_specs(&(params->car_info[ind].specs));
        }
    }
    if (self->last_boosted_id != last_id) {
        modify_specs(last_specs);
        self->last_boosted_id = last_id;
    }
    self->step++;
}

extern "C" {
    void* init() {
        auto *self = (BoostLast_t*) malloc(sizeof(BoostLast_t));
        self->step = 0;
        self->last_boosted_id = -1;
        return self;
    }
    void execute(BoostLast_t *self, DTO_Info *params) {
        run(self, params);
    }
    void destroy(BoostLast_t *self) {
        free(self);
    }

}