#include <cstdint>
#include "Dirt.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

Dirt::Dirt(int32_t x, int32_t y, int32_t rotation):
        Terrain(x, y, rotation)
{}

UpdateClient Dirt::get_to_send() {
    int32_t x = METER_TO_PIXEL * (this->map_x - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * (this->map_y - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, TYPE_DIRT, x, y, 0/*rotation*/};
    return UpdateClient(std::move(update_info));
}
