#include <memory>
#include "TerrainFactory.h"
#include <common/EntityType.h>
#include "Dirt.h"
#include "Grass.h"
#include "Sand.h"
#include "Asphalt.h"

std::unique_ptr<Terrain> TerrainFactory::create_terrain(int32_t entity_id, int32_t x, int32_t y, int32_t rotation) {
    switch (entity_id) {
        case TYPE_GRASS:
            return std::unique_ptr<Terrain> (new Grass(x, y, rotation));
        case TYPE_ASPHALT:
            return std::unique_ptr<Terrain> (new Asphalt(x, y, rotation));
        case TYPE_SAND:
            return std::unique_ptr<Terrain> (new Sand(x, y, rotation));
        case TYPE_DIRT:
            return std::unique_ptr<Terrain> (new Dirt(x, y, rotation));
    }
}
