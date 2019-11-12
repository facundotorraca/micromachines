#ifndef MICROMACHINES_DIRT_H
#define MICROMACHINES_DIRT_H

#include "Terrain.h"
#include <model/Vehicle/Wheel.h>

class Dirt : public Terrain {
    public:
        Dirt(int32_t ID, int32_t x, int32_t y);

        void apply_terrain_effect(Body* wheel) override;

        void set_terrain_user_data() override;
};


#endif //MICROMACHINES_DIRT_H
