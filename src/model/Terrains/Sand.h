#ifndef MICROMACHINES_SAND_H
#define MICROMACHINES_SAND_H

#include "Terrain.h"

class Sand : public Terrain {
    public:
        Sand(int32_t x, int32_t y, int32_t rotation, int32_t ID);

        UpdateClient get_to_send() override;

        void apply_terrain_effect(Wheel* wheel) override;

        void set_terrain_user_data() override;
};


#endif //MICROMACHINES_SAND_H
