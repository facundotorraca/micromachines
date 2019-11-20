//
// Created by javier on 24/10/19.
//

#include "Map.h"
#include <SDL2/SDL.h>

#define BACK_TILES 50

void Map::draw(Camera& camera) {
    int tile_width = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    if (back_tex)
        for (int32_t i = -1; i < back.n_mega_tiles; i++){
            for (int32_t j = -1; j < back.n_mega_tiles; j++){
                camera.drawExternalWorldTexture(back_tex, i*BACK_TILES*tile_width, j*BACK_TILES*tile_width, 
                        BACK_TILES*tile_width, BACK_TILES*tile_width, 0, false);
            }
        }
    for (auto& tile : tiles){
        tile.draw(camera);
    }
}

void Map::addTile(TileInfo &info) {
    if (info.type != back.type)
        tiles.emplace_back(info);
}

void Map::setBackground(int32_t type, int32_t width, int32_t height, Camera& camera) {
    back = {type, width, height};
    int32_t tile_width = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    SDL_Surface* back_surf = SDL_CreateRGBSurfaceWithFormat(0, 
            BACK_TILES*tile_width, BACK_TILES*tile_width, 32, SDL_PIXELFORMAT_RGBA32);
    if (!back_surf)
        std::cerr <<" creating back_surf failed: " << SDL_GetError() << std::endl;
    Texture tex = camera.getTexture(type);
    SDL_Surface* aux_surf = SDL_CreateRGBSurfaceWithFormat(0,
            tex.surf->w, tex.surf->h, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_BlitSurface(tex.surf, nullptr, aux_surf, nullptr);
    for (int32_t i = 0; i < BACK_TILES; i++) {
        for (int32_t j = 0; j < BACK_TILES; j++) {
            SDL_Rect tile_dst{i * tile_width, j * tile_width,
                              tile_width + 5, tile_width + 5};
            SDL_BlitScaled(aux_surf, nullptr, back_surf, &tile_dst);
        }
    }
    back_tex = camera.createTexture(back_surf);
    SDL_FreeSurface(back_surf);

    back.n_mega_tiles = ceil((float)width/BACK_TILES)+1;
}

Map::Map() : back_tex(nullptr), back({0, 0, 0}){}

Map::~Map() {
    if (back_tex)
        SDL_DestroyTexture(back_tex);
}
