#include "Sand.h"
#include <cstdint>
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define SAND_SPEED_PROPORTION 0.1f
#define SAND_TRACTION_PROPORTION 0.3f

Sand::Sand(int32_t x, int32_t y, int32_t rotation, int32_t ID):
    Terrain(x, y, rotation, ID)
{}

UpdateClient Sand::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, this->ID, x, y, this->rotation};
    return UpdateClient(std::move(update_info));
}

void Sand::apply_terrain_effect(Body* wheel) {
    ((Wheel*)wheel)->set_traction(SAND_TRACTION_PROPORTION);
    ((Wheel*)wheel)->reduce_max_speed(SAND_SPEED_PROPORTION);
}

void Sand::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}
