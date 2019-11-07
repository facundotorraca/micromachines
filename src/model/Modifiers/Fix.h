#ifndef MICROMACHINES_FIX_H
#define MICROMACHINES_FIX_H

#include "Modifier.h"
#include <common/EntityType.h>

class Fix : public Modifier {

    public:
        Fix(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y)
        {}

        int32_t get_modifier_type() override {
            return TYPE_FIX;
        }

};

#endif //MICROMACHINES_FIX_H
