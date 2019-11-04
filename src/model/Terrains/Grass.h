#ifndef MICROMACHINES_GRASS_H
#define MICROMACHINES_GRASS_H

#include <vector>
#include <cstdint>
#include "Terrain.h"

class Grass : public Terrain {
    public:
        Grass(int32_t x, int32_t y, int32_t rotation, int32_t ID);

        UpdateClient get_to_send() override;

        void apply_terrain_effect(Body* wheel) override;

        void set_terrain_user_data() override;
};


#endif //MICROMACHINES_GRASS_H
