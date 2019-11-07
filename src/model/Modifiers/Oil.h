#ifndef MICROMACHINES_OIL_H
#define MICROMACHINES_OIL_H

#include <cstdint>
#include "Modifier.h"
#include <common/EntityType.h>

class Oil : public Modifier {

    public:
        Oil(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y, TILE_TERRAIN_SIZE/2)
        {}

        int32_t get_modifier_type() override {
            return TYPE_OIL;
        }

        void set_modifier_user_data() override {
            this->modifier_fixture->SetUserData(this);
        }

        void apply_modifier_effect(Body* body) override {
        }

};


#endif //MICROMACHINES_OIL_H
