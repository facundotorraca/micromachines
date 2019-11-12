#include <cstdint>
#include "Asphalt.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>

Asphalt::Asphalt(int32_t ID, int32_t x, int32_t y):
    Terrain(ID, x, y)
{}

void Asphalt::apply_terrain_effect(Body* body) {
    if (body->get_ID() == TYPE_WHEEL)
        ((Wheel *) body)->restore_specs();
    if (body->get_ID() == TYPE_CAR)
        ((Car *) body)->set_respawn(this->coordinate);
}

void Asphalt::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}

