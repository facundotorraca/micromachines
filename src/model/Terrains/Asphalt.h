#ifndef MICROMACHINES_ASPHALT_H
#define MICROMACHINES_ASPHALT_H

#include "Terrain.h"

class Asphalt : public Terrain  {
    public:
        Asphalt(int32_t x, int32_t y, int32_t rotation, int32_t ID);

        UpdateClient get_to_send() override;

        void apply_terrain_effect(Wheel* wheel) override;

        void set_terrain_user_data() override;
};

#endif //MICROMACHINES_ASPHALT_H
