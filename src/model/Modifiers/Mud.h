#ifndef MICROMACHINES_MUD_H
#define MICROMACHINES_MUD_H

#include "Modifier.h"
#include <common/EntityType.h>

class Mud : public Modifier {

    public:
        Mud(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y, TILE_TERRAIN_SIZE/2)
        {}

        int32_t get_modifier_type() override {
            return TYPE_MUD;
        }

        void set_modifier_user_data() override {
            this->modifier_fixture->SetUserData(this);
        }

        void apply_modifier_effect(Body* body) override {
            ((Car*)body)->apply_mud_effect();
        }
};


#endif //MICROMACHINES_MUD_H
