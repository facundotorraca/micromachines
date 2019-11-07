#ifndef MICROMACHINES_ROCK_H
#define MICROMACHINES_ROCK_H

#include "Modifier.h"
#include <common/EntityType.h>

class Rock : public Modifier {

    public:
        Rock(int32_t time_of_life, int32_t map_x, int32_t map_y):
            Modifier(time_of_life, map_x, map_y)
        {}

        int32_t get_modifier_type() override {
            return TYPE_ROCK;
        }


};


#endif //MICROMACHINES_ROCK_H
