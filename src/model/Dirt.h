#ifndef MICROMACHINES_DIRT_H
#define MICROMACHINES_DIRT_H

#include "Terrain.h"

class Dirt : public Terrain {
    public:
        Dirt(int32_t x, int32_t y, int32_t rotation);

        UpdateClient get_to_send() override;
};


#endif //MICROMACHINES_DIRT_H
