#include <fstream>
#include <iostream>
#include <utility>
#include "MapLoader.h"
#include "json/json.hpp"
#include <model/Terrains/TerrainFactory.h>
#include <common/EntityType.h>

#define FIRST_LAYER 0

#define ID_PROPERTY_POS 0
#define ROTATION_PROPERTY_POS 1
#define STATIC_PROPERTY_POS 2

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

    racing_track.set_track_size(json_map_data["height"], json_map_data["width"]);
    racing_track.set_track_terrain(TYPE_GRASS);

    std::vector<Coordinate> finish_line; //Stores beginning and end coordinate of the finish line
    for (int i = 0; i < json_map_data["height"]; i++) {
        for (int j = 0; j < json_map_data["width"]; j++) {

            unsigned ID_pos = unsigned(json_map_data["layers"][FIRST_LAYER]["data"][j * (int)json_map_data["height"] + i]) - 1;
            int32_t type_ID = json_tiles_data["tiles"][ID_pos]["properties"][ID_PROPERTY_POS]["value"];
            int32_t tile_rotation = json_tiles_data["tiles"][ID_pos]["properties"][ROTATION_PROPERTY_POS ]["value"];
            bool is_static = json_tiles_data["tiles"][ID_pos]["properties"][STATIC_PROPERTY_POS ]["value"];

            if (is_static) {
                racing_track.add_static_track_object(std::move(StaticTrackObject(type_ID ,i, j, tile_rotation)));
            } else {
                racing_track.add_terrain(std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation)));
            }

            if (type_ID == TYPE_SPAWN_POINT) {
                this->spawn_points.emplace_back(float(i), float(j), float(tile_rotation));
            }

            if (type_ID == TYPE_FINISH_LINE_BORDER) {
                finish_line.emplace_back(float(i), float(j), float(tile_rotation));
            }
        }
    }
    if (finish_line.size() == 2) racing_track.set_finish_line(finish_line[0], finish_line[1]);
}

void MapLoader::set_cars_spawn_point(std::unordered_map<int32_t, Car>& cars) {
    int spawn_point_pos = this->spawn_points.size() - 1; //Start from end to beginning
    for (auto &car : cars) {
        car.second.set_spawn_point(this->spawn_points[spawn_point_pos]);
        spawn_point_pos--;
    }
}
