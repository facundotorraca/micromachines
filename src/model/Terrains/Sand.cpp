#include "Sand.h"
#include <cstdint>
#include <common/Sizes.h>
#include "model/FixtureUserData.h"
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define SAND_SPEED_PROPORTION 0.1f
#define SAND_TRACTION_PROPORTION 0.3f

Sand::Sand(int32_t x, int32_t y, int32_t rotation):
    Terrain(x, y, rotation)
{}

UpdateClient Sand::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, TYPE_SAND, x, y, 0/*rotation*/};
    return UpdateClient(std::move(update_info));
}

void Sand::set_terrain_user_data() {
    this->terrain_body->SetUserData(this); //Set a self reference to handler collisions
    this->terrain_fixture->SetUserData(new SandUserData());
}

void Sand::apply_effect(Wheel* wheel) {
    wheel->set_traction(SAND_TRACTION_PROPORTION);
    wheel->reduce_max_speed(SAND_SPEED_PROPORTION);
}
