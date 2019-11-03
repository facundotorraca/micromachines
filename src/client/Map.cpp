//
// Created by javier on 24/10/19.
//

#include "Map.h"

void Map::draw(Camera& camera) {
    for (int i=0; i < back.width; i++)
        for (int j=0; j < back.height; j++)
            camera.drawWorldTexture(back.type, TILE_TERRAIN_SIZE*METER_TO_PIXEL*i,
                    TILE_TERRAIN_SIZE*METER_TO_PIXEL*j, 0);
    for (auto& tile : tiles){
        tile.draw(camera);
    }
}

void Map::addTile(TileInfo &info) {
    tiles.emplace_back(info);
}

void Map::setBackground(int32_t type, int32_t width, int32_t height) {
    back = {type, width, height};
}

Map::Map() : back({0, 0, 0}){}
