#include <cstdint>
#include "Grass.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define GRASS_SPEED_PROPORTION 0.3f
#define GRASS_TRACTION_PROPORTION 0.5f

Grass::Grass(int32_t ID, int32_t x, int32_t y):
    Terrain(ID, x, y)
{}

void Grass::apply_terrain_effect(Body* body) {
    if (body->get_ID() == TYPE_WHEEL) {
        ((Wheel *)body)->reduce_max_traction(GRASS_TRACTION_PROPORTION);
        ((Wheel*)body)->reduce_max_speed(GRASS_SPEED_PROPORTION);
    }
}

void Grass::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}
