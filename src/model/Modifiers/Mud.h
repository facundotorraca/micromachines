#ifndef MICROMACHINES_MUD_H
#define MICROMACHINES_MUD_H

#include "Modifier.h"
#include <common/EntityType.h>

class Mud : public Modifier {

    public:
        Mud(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y)
        {}

        int32_t get_modifier_type() override {
            return TYPE_MUD;
        }

};


#endif //MICROMACHINES_MUD_H
