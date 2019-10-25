#ifndef MICROMACHINES_GRASS_H
#define MICROMACHINES_GRASS_H

#include <vector>
#include <cstdint>
#include "Terrain.h"

class Grass : public Terrain {

    public:
        Grass(int32_t x, int32_t y, int32_t rotation);

        UpdateClient get_to_send() override;

};


#endif //MICROMACHINES_GRASS_H
