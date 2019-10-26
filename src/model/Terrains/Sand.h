#ifndef MICROMACHINES_SAND_H
#define MICROMACHINES_SAND_H

#include "Terrain.h"

class Sand : public Terrain {
    private:
        void set_terrain_user_data() override;

    public:
        Sand(int32_t x, int32_t y, int32_t rotation);

        UpdateClient get_to_send() override;

        void apply_effect(Wheel* wheel) override;
};


#endif //MICROMACHINES_SAND_H
