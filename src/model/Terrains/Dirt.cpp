#include "Dirt.h"
#include <cstdint>
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include "model/FixtureUserData.h"
#include <common/EntityType.h>

#define DIRT_TRACTION 0.75f

Dirt::Dirt(int32_t x, int32_t y, int32_t rotation):
        Terrain(x, y, rotation)
{}

UpdateClient Dirt::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, TYPE_DIRT, x, y, 0/*rotation*/};
    return UpdateClient(std::move(update_info));
}

void Dirt::set_terrain_user_data() {
    this->terrain_body->SetUserData(this); //Set a self reference to handler collisions
    this->terrain_fixture->SetUserData(new DirtUserData());
}

void Dirt::apply_effect(Wheel* wheel) {
    wheel->set_traction(DIRT_TRACTION);
}
