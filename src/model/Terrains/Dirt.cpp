#include "Dirt.h"
#include <cstdint>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>

#define DIRT_SPEED_PROPORTION 0.5f
#define DIRT_TRACTION_PROPORTION 0.7f

Dirt::Dirt(int32_t ID, int32_t x, int32_t y):
    Terrain(ID, x, y)
{}

void Dirt::apply_terrain_effect(Body* body) {
    if (body->get_ID() == TYPE_WHEEL) {
        ((Wheel*)body)->reduce_max_speed(DIRT_SPEED_PROPORTION);
        ((Wheel *)body)->reduce_max_traction(DIRT_TRACTION_PROPORTION);
    }
    if (body->get_ID() == TYPE_CAR)
        ((Car*)body)->set_respawn(this->coordinate);
}

void Dirt::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}