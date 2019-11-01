#include "Dirt.h"
#include <cstdint>
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include "model/FixtureUserData.h"
#include <common/EntityType.h>

#define DIRT_SPEED_PROPORTION 0.5f
#define DIRT_TRACTION_PROPORTION 0.7f

Dirt::Dirt(int32_t x, int32_t y, int32_t rotation, int32_t ID):
        Terrain(x, y, rotation, ID)
{}

UpdateClient Dirt::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, this->ID, x, y, this->rotation};
    return UpdateClient(std::move(update_info));
}

void Dirt::apply_terrain_effect(Wheel* wheel) {
    ((Wheel*)wheel)->reduce_max_speed(DIRT_SPEED_PROPORTION);
    ((Wheel*)wheel)->set_traction(DIRT_TRACTION_PROPORTION);
}

void Dirt::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}
