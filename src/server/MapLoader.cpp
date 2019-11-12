#include <fstream>
#include <iostream>
#include <utility>
#include "MapLoader.h"
#include "json/json.hpp"
#include <model/RacingTrack.h>
#include <common/EntityType.h>
#include <model/Dijkstra.h>
#include <model/Terrains/TerrainFactory.h>
#include <common/MsgTypes.h>

#define BEGIN_TRACK_TILE 26

#define TILES_LAYER 0
#define PROPERTIES_LAYER 1

#define ID_PROPERTY_POS 0
#define ROTATION_PROPERTY_POS 1
#define STATIC_PROPERTY_POS 2
#define ORIENTATION_PROPERTY_POS 0
#define EXPLOSIVE_PROPERTY_POS 0


#define ORIENTATION_UP 1
#define ORIENTATION_DOWN 2
#define ORIENTATION_LEFT 3
#define ORIENTATION_RIGHT 4

using json = nlohmann::json;

bool is_track(int32_t type_ID) {
    return (type_ID >= 0 && type_ID <= 27) ||
           (type_ID >= 29 && type_ID <= 55) ||
           (type_ID >= 63 && type_ID <= 89);
}

bool are_adjacent(std::unique_ptr<Terrain>& t_a, std::unique_ptr<Terrain>& t_b) {
    Coordinate a = t_a->get_map_coordinate();
    Coordinate b = t_b->get_map_coordinate();
    return  a.is_adjacent_to(b);
}

void set_track_to_race(std::vector<std::unique_ptr<Terrain>>& track, RacingTrack& racing_track) {
    for (auto& track_part : track) {
        racing_track.add_track(std::move(track_part));
    }
}

void send_tile(int32_t type_ID, int32_t x_map, int32_t y_map, int32_t rot, ClientUpdater &updater) {
    int32_t x = METER_TO_PIXEL * ((x_map * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((y_map * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, type_ID, x, y, rot};
    updater.send_to_all(UpdateClient(std::move(update_info)));
}

void set_orientation(std::unique_ptr<Terrain>& track, int orientation) {
    switch (orientation) {
        case ORIENTATION_UP:
            track->set_orientation(UP);
            break;
        case ORIENTATION_DOWN:
            track->set_orientation(DOWN);
            break;
        case ORIENTATION_RIGHT:
            track->set_orientation(RIGHT);
            break;
        case ORIENTATION_LEFT:
            track->set_orientation(LEFT);
            break;
        default:
            break;
    }
}

MapLoader::MapLoader(std::string map_path, std::string map_name) {
    this->map_paths = std::move(map_path);
    this->map_name = std::move(map_name);
}

void MapLoader::open_files(nlohmann::json &json_map_file, nlohmann::json& json_tiles_file) {
    std::ifstream map_file(this->map_paths + this->map_name);
    if (!map_file.is_open()) {
        std::cerr << "MAP FILE ERROR\n";
        return;
    }
    map_file >> json_map_file;

    std::ifstream tiles_file(this->map_paths + (std::string)json_map_file["tilesets"][0]["source"]);
    if (!tiles_file.is_open()) {
        std::cerr << "MAP TILE ERROR\n";
        return;
    }
    tiles_file >> json_tiles_file;
}

void MapLoader::add_tile_behaviour(int32_t type_ID, int32_t i, int32_t j, int32_t rot, RacingTrack& racing_track) {
    switch (type_ID) {
        case TYPE_SPAWN_POINT:
            racing_track.add_spawn_point(Coordinate(float(i), float(j), float(rot)));
            break;
        case TYPE_FINISH_LINE_BORDER:
            finish_line.emplace_back(float(i), float(j), float(rot));
            break;
        case TYPE_F_PLACE_PODIUM:
            podium.insert(std::pair<int32_t, Coordinate>(1, Coordinate(float(i), float(j), float(rot))));
            break;
        case TYPE_S_PLACE_PODIUM:
            podium.insert(std::pair<int32_t, Coordinate>(2, Coordinate(float(i), float(j), float(rot))));
            break;
        case TYPE_T_PLACE_PODIUM:
            podium.insert(std::pair<int32_t, Coordinate>(3, Coordinate(float(i), float(j), float(rot))));
            break;
        case TYPE_NO_PODIUM_PLACE:
            break;
            //podium.insert(std::pair<int32_t, Coordinate>(3, Coordinate(float(i), float(j), float(tile_rotation))));
        default:
            break;
    }
}

void MapLoader::load_map(RacingTrack &racing_track, ClientUpdater& updater) {
    json json_map_data;
    json json_tiles_data;
    this->open_files(json_map_data, json_tiles_data);

    int map_width = json_map_data["width"];
    int map_height = json_map_data["height"];

    updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_SET_BACKGROUND , TYPE_GRASS, map_height, map_width}));

    std::unique_ptr<Terrain> begin_tile(nullptr); //used to store the begin tile.

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {

            auto ID_pos = unsigned(json_map_data["layers"][TILES_LAYER]["data"][j * (int) json_map_data["height"] + i]) - 1;
            int32_t type_ID = json_tiles_data["tiles"][ID_pos]["properties"][ID_PROPERTY_POS]["value"];

            int32_t tile_rotation = json_tiles_data["tiles"][ID_pos]["properties"][ROTATION_PROPERTY_POS]["value"];
            bool is_static = json_tiles_data["tiles"][ID_pos]["properties"][STATIC_PROPERTY_POS]["value"];
            auto info_pos = unsigned(json_map_data["layers"][PROPERTIES_LAYER]["data"][j * (int) json_map_data["height"] + i]) - 1;

            send_tile(type_ID, i, j, tile_rotation, updater);

            if (is_static)
                racing_track.add_static_track_object(std::move(StaticTrackObject(type_ID, i, j)));
            else {
                if (is_track(type_ID) && type_ID == BEGIN_TRACK_TILE) {
                    begin_tile = std::move(TerrainFactory::create_terrain(type_ID, i, j));
                }
                else if (is_track(type_ID) && ((type_ID == TYPE_FINISH_LINE_BORDER) || (type_ID == TYPE_FINISH_LINE_CENTER))) {
                    racing_track.add_track((std::move(TerrainFactory::create_terrain(type_ID, i, j))));
                }
                else if (is_track(type_ID)) {
                    this->track.push_back((std::move(TerrainFactory::create_terrain(type_ID, i, j))));
                    int32_t orientation = json_tiles_data["tiles"][info_pos]["properties"][ORIENTATION_PROPERTY_POS]["value"];
                    set_orientation(this->track.back(), orientation);
                }
                else {
                    bool is_limit = json_tiles_data["tiles"][info_pos]["properties"][EXPLOSIVE_PROPERTY_POS]["value"];
                    std::unique_ptr<Terrain> terrain = std::move(TerrainFactory::create_terrain(type_ID, i, j));
                    if (is_limit)
                        terrain->set_as_limit();
                    racing_track.add_terrain(std::move(terrain));
                }
            }

            this->add_tile_behaviour(type_ID, i, j, tile_rotation, racing_track);
        }
    }

    this->track.push_back(std::move(begin_tile));
    this->set_begin_distance_to_tiles();
    set_track_to_race(this->track, racing_track);

    if (finish_line.size() == 2) racing_track.set_finish_line(finish_line[0], finish_line[1]);
    if (podium.size() == 3) racing_track.set_podium(podium.at(1), podium.at(2), podium.at(3));
}



void MapLoader::set_begin_distance_to_tiles() {
    std::vector<std::vector<int32_t> > graph(this->track.size());

    for (size_t row = 0; row < this->track.size(); row++) {
        for (auto &col : this->track)
            graph[row].emplace_back(are_adjacent(this->track[row], col) ? 1 : 0);
    }

    std::vector<int32_t> distances(this->track.size());
    size_t begin_tile_pos = this->track.size() - 1;
    Dijkstra::dijkstra(graph, distances, begin_tile_pos);

    for (size_t i = 0; i < distances.size(); i++)
        this->track[i]->set_begin_distance(distances[i]);
}


