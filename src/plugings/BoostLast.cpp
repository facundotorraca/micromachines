//
// Created by alejo on 7/11/19.
//

#include <model/DTO_Info.h>
#include <iostream>

typedef struct self {
    uint32_t step;
    int32_t last_boosted_id;
} BoostLast_t;

void run(BoostLast_t *self, DTO_Info *params) {
    self->step++;
    std::cout << "Running BOST LAST pluging " << self->step << std::endl;
    size_t last = 0;
    int32_t last_id = 0;
    float *last_speed = NULL;
    for (size_t ind = 0; ind < params->cars; ind++) {
        if (params->car_info[ind].position > last) {
            last = params->car_info[ind].position;
            last_speed = &(params->car_info[ind].specs.max_forward_speed);
            last_id = params->car_info[ind].ID;
        }
        if (params->car_info[ind].ID == self->last_boosted_id) {
            params->car_info[ind].specs.max_forward_speed = 0;
        }
    }
    if (self->last_boosted_id != last_id) {
        *last_speed = *last_speed * 2;
        self->last_boosted_id = last_id;
    }
}

extern "C" {
    void* init() {
        BoostLast_t *self = (BoostLast_t*) malloc(sizeof(BoostLast_t));
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