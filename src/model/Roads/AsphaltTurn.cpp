#include "AsphaltTurn.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>

AsphaltTurn::AsphaltTurn(int32_t x, int32_t y, int32_t rotation):
    Asphalt(x, y, rotation)
{}

UpdateClient AsphaltTurn::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, TYPE_ASPHALT_TURN, x, y, this->rotation};
    return UpdateClient(std::move(update_info));
}
