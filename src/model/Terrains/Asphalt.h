#ifndef MICROMACHINES_ASPHALT_H
#define MICROMACHINES_ASPHALT_H

#include "Terrain.h"

class Asphalt : public Terrain  {
    public:
        Asphalt(int32_t ID, int32_t x, int32_t y);

        void apply_terrain_effect(Body* wheel) override;

        void set_terrain_user_data() override;
};

#endif //MICROMACHINES_ASPHALT_H
