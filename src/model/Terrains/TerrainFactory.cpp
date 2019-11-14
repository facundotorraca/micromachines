#include <memory>
#include <model/FinishLine.h>
#include "Dirt.h"
#include "Sand.h"
#include "Grass.h"
#include "Asphalt.h"
#include "TerrainFactory.h"

#define BEG_ASPHALT_IDS 1
#define END_ASPHALT_IDS 27

#define BEG_DIRT_IDS 28
#define END_DIRT_IDS 55

#define BEG_GRASS_IDS 56
#define END_GRASS_IDS 59

std::unique_ptr<Terrain> TerrainFactory::create_terrain(int32_t ID, int32_t x, int32_t y) {
    if (ID >= BEG_ASPHALT_IDS && ID <= END_ASPHALT_IDS )
        return std::unique_ptr<Terrain> (new Asphalt(ID, x, y));
    if (ID >= BEG_DIRT_IDS && ID <= END_DIRT_IDS )
        return std::unique_ptr<Terrain> (new Dirt(ID, x, y));
    if (ID >= BEG_GRASS_IDS && ID <= END_GRASS_IDS )
        return std::unique_ptr<Terrain> (new Grass(ID, x, y));
    return std::unique_ptr<Terrain> (new Sand(ID, x, y));
}
