#include "Sand.h"
#include <cstdint>
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>

#define SAND_SPEED_PROPORTION 0.1f
#define SAND_TRACTION_PROPORTION 0.3f

Sand::Sand(int32_t ID, int32_t x, int32_t y):
        Terrain(ID, x, y)
{}

void Sand::apply_terrain_effect(Body* body) {
    if (body->get_ID() == TYPE_WHEEL) {
        ((Wheel*)body)->reduce_max_speed(SAND_SPEED_PROPORTION);
        ((Wheel *)body)->reduce_max_traction(SAND_TRACTION_PROPORTION);
    }
    if (body->get_ID() == TYPE_CAR)
        ((Car*)body)->set_respawn(this->coordinate);;

}

void Sand::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}
