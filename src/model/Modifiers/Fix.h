#ifndef MICROMACHINES_FIX_H
#define MICROMACHINES_FIX_H

#include "Modifier.h"
#include <model/Body.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>

class Fix : public Modifier {

    public:
        Fix(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y, TILE_TERRAIN_SIZE/2)
        {}

        int32_t get_modifier_type() override {
            return TYPE_FIX;
        }

        void set_modifier_user_data() override {
            this->modifier_fixture->SetUserData(this);
        }

        void apply_modifier_effect(Body* body) override {
            if (body->get_ID() == TYPE_CAR) {
                ((Car*)body)->repair();
                this->remaining_time = 0; //destroy itself
            }
        }
};

#endif //MICROMACHINES_FIX_H
