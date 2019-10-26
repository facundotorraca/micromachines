#include <fstream>
#include <iostream>
#include <utility>
#include "MapLoader.h"
#include "json/json.hpp"
#include <model/Terrains/TerrainFactory.h>

#define FIRST_LAYER 0
#define ID_PROPERTIE_POS 0

using json = nlohmann::json;

MapLoader::MapLoader(std::string map_path) {
    this->map_paths = std::move(map_path);
}

void MapLoader::load_map(RacingTrack &racing_track, const std::string& map_filename, const std::string& tiles_filename) {
    std::ifstream map_file(this->map_paths + map_filename);
    std::ifstream tiles_file(this->map_paths + tiles_filename);

    if (!map_file.is_open() || !tiles_file.is_open()) {
        std::cout << "FILE ERROR\n";
        return; //Aca va una excepcion
    }

    json json_map_data; map_file >> json_map_data;
    json json_tiles_data; tiles_file >> json_tiles_data;

    for (int i = 0; i < json_map_data["height"]; i++) {
        for (int j = 0; j < json_map_data["width"]; j++) {

            unsigned ID_pos = unsigned(json_map_data["layers"][FIRST_LAYER]["data"][j * (int)json_map_data["height"] + i]) - 1;
            int32_t type_ID = json_tiles_data["tiles"][ID_pos]["properties"][ID_PROPERTIE_POS]["value"];

            racing_track.add_map_part(std::move(TerrainFactory::create_terrain(type_ID, i, j, 0)));
        }
    }
}