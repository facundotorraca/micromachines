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

void MapLoader::load_map(RacingTrack &racing_track, const std::string& map_filename) {
    std::ifstream map_file(this->map_paths + map_filename);

    if (!map_file.is_open()) {
        std::cerr << "MAP FILE ERROR\n";
        return; //ACA VA EXCEPION
    }

    json json_map_data; map_file >> json_map_data;

    std::ifstream tiles_file(this->map_paths + (std::string)json_map_data["tilesets"][0]["source"]);

    if (!tiles_file.is_open()) {
        std::cerr << "MAP TILE ERROR\n";
        return; //ACA VA EXCEPION
    }

    json json_tiles_data; tiles_file >> json_tiles_data;

    racing_track.set_track_size(json_map_data["height"], json_map_data["width"]);
    racing_track.set_track_terrain(TYPE_GRASS);

    std::unordered_map<int32_t, Coordinate> podium;
    std::vector<Coordinate> finish_line; //Stores beginning and end coordinate of the finish line

    for (int i = 0; i < json_map_data["height"]; i++) {
        for (int j = 0; j < json_map_data["width"]; j++) {

            unsigned ID_pos = unsigned(json_map_data["layers"][FIRST_LAYER]["data"][j * (int) json_map_data["height"] + i]) - 1;
            int32_t type_ID = json_tiles_data["tiles"][ID_pos]["properties"][ID_PROPERTY_POS]["value"];

            int32_t tile_rotation = json_tiles_data["tiles"][ID_pos]["properties"][ROTATION_PROPERTY_POS]["value"];
            bool is_static = json_tiles_data["tiles"][ID_pos]["properties"][STATIC_PROPERTY_POS]["value"];

            if (is_static) {
                racing_track.add_static_track_object(std::move(StaticTrackObject(type_ID ,i, j, tile_rotation)));
            } else {
                if ((type_ID >= 0 && type_ID <= 27) || (type_ID >= 29 && type_ID <= 55)  || (type_ID >= 63 && type_ID <= 89))
                    racing_track.add_track(std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation)));
                else
                    racing_track.add_terrain(std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation)));
            }

            switch (type_ID) {
                case TYPE_SPAWN_POINT:
                    racing_track.add_spawn_point(Coordinate(float(i), float(j), float(tile_rotation)));
                    break;
                case TYPE_FINISH_LINE_BORDER:
                    finish_line.emplace_back(float(i), float(j), float(tile_rotation)); break;
                case TYPE_F_PLACE_PODIUM:
                    podium.insert(std::pair<int32_t, Coordinate>(1, Coordinate(float(i), float(j), float(tile_rotation))));
                    break;
                case TYPE_S_PLACE_PODIUM:
                    podium.insert(std::pair<int32_t, Coordinate>(2, Coordinate(float(i), float(j), float(tile_rotation))));
                    break;
                case TYPE_T_PLACE_PODIUM:
                    podium.insert(std::pair<int32_t, Coordinate>(3, Coordinate(float(i), float(j), float(tile_rotation))));
                    break;
                case TYPE_NO_PODIUM_PLACE:
                    break;
                    //podium.insert(std::pair<int32_t, Coordinate>(3, Coordinate(float(i), float(j), float(tile_rotation))));
                default:
                    break;
            }
        }
    }

    if (finish_line.size() == 2) racing_track.set_finish_line(finish_line[0], finish_line[1]);
    if (podium.size() == 3) racing_track.set_podium(podium.at(1), podium.at(2),podium.at(3));
}

