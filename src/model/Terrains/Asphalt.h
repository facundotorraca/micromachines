#ifndef MICROMACHINES_ASPHALT_H
#define MICROMACHINES_ASPHALT_H

#include "Terrain.h"

class Asphalt : public Terrain {

    private:
        void set_terrain_user_data() override;

    public:

        Asphalt(int32_t x, int32_t y, int32_t rotation, int32_t ID);

        UpdateClient get_to_send() override;

        void apply_effect(Wheel* wheel) override;

        ~Asphalt();

};

#endif //MICROMACHINES_ASPHALT_H
