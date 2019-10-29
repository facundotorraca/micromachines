#include <memory>
#include "Dirt.h"
#include "Sand.h"
#include "Grass.h"
#include "TerrainFactory.h"
#include "Asphalt.h"
#include <common/EntityType.h>
#include <iostream>

#define BEG_ASPHALT_IDS 1
#define END_ASPHALT_IDS 27

#define BEG_DIRT_IDS 28
#define END_DIRT_IDS 55

#define BEG_GRASS_IDS 56
#define END_GRASS_IDS 59

#define BEG_SAND_IDS 60
#define END_SAND_IDS 89

#define BEG_OBJECTS_ID 90
#define END_OBJECTS_IDS 138


std::unique_ptr<Terrain> TerrainFactory::create_terrain(int32_t entity_id, int32_t x, int32_t y, int32_t rotation) {
    if (entity_id >= BEG_ASPHALT_IDS && entity_id <= END_ASPHALT_IDS ) return std::unique_ptr<Terrain> (new Asphalt(x, y, rotation, entity_id));
    if (entity_id >= BEG_DIRT_IDS && entity_id <= END_DIRT_IDS ) return std::unique_ptr<Terrain> (new Dirt(x, y, rotation, entity_id));
    if (entity_id >= BEG_GRASS_IDS && entity_id <= END_GRASS_IDS ) return std::unique_ptr<Terrain> (new Grass(x, y, rotation, entity_id));
    if (entity_id >= BEG_SAND_IDS && entity_id <= END_SAND_IDS ) return std::unique_ptr<Terrain> (new Sand(x, y, rotation, entity_id));
    if (entity_id >= BEG_OBJECTS_ID && entity_id <= END_OBJECTS_IDS ) return std::unique_ptr<Terrain> (new Grass(x, y, rotation, entity_id)); //este hay que cambiarlo
}
