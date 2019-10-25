#include <cstdint>
#include "Asphalt.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

Asphalt::Asphalt(int32_t x, int32_t y, int32_t rotation):
        Terrain(x, y, rotation)
{}

UpdateClient Asphalt::get_to_send() {
    int32_t x = METER_TO_PIXEL * (this->map_x - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * (this->map_y - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, TYPE_ASPHALT, x, y, 0/*rotation*/};
    return UpdateClient(std::move(update_info));
}
