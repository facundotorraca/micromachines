#ifndef MICROMACHINES_TERRAINFACTORY_H
#define MICROMACHINES_TERRAINFACTORY_H

#include <memory>
#include <cstdint>
#include "Terrain.h"

class TerrainFactory {

    public:
        static std::unique_ptr<Terrain>  create_terrain(int32_t entity_id, int32_t x, int32_t y, int32_t rotation);
};

#endif //MICROMACHINES_TERRAINFACTORY_H
