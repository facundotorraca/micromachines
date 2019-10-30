//
// Created by javier on 24/10/19.
//

#include "Map.h"

void Map::draw(Camera& camera) {
    camera.drawBackground(back.type, back.width, back.height);
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
