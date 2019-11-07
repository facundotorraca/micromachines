#ifndef MICROMACHINES_OIL_H
#define MICROMACHINES_OIL_H

#include <cstdint>
#include "Modifier.h"
#include <common/EntityType.h>

class Oil : public Modifier {

    public:
        Oil(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y)
        {}

        int32_t get_modifier_type() override {
            return TYPE_OIL;
        }

};


#endif //MICROMACHINES_OIL_H
