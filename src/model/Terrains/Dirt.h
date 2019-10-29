#ifndef MICROMACHINES_DIRT_H
#define MICROMACHINES_DIRT_H

#include "Terrain.h"
#include <model/Vehicle/Wheel.h>

class Dirt : public Terrain {
    private:
        void set_terrain_user_data() override;

    public:
        Dirt(int32_t x, int32_t y, int32_t rotation, int32_t ID);

        UpdateClient get_to_send() override;

        void apply_effect(Wheel* wheel) override;
};


#endif //MICROMACHINES_DIRT_H
