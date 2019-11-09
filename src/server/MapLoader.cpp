#include <fstream>
#include <iostream>
#include <utility>
#include "MapLoader.h"
#include "json/json.hpp"
#include <common/EntityType.h>
#include <model/Terrains/TerrainFactory.h>
#include <model/Dijkstra.h>

#define BEGIN_TRACK_TILE 26
#define FIRST_LAYER 0

#define ID_PROPERTY_POS 0
#define ROTATION_PROPERTY_POS 1
#define STATIC_PROPERTY_POS 2

#define NOT_EDGE 0
#define INF 999999

using json = nlohmann::json;

MapLoader::MapLoader(std::string map_path) {
    this->map_paths = std::move(map_path);
}

void MapLoader::open_files(nlohmann::json &json_map_file, nlohmann::json& json_tiles_file, const std::string& map_filename) {
    std::ifstream map_file(this->map_paths + map_filename);
    if (!map_file.is_open()) {
        std::cerr << "MAP FILE ERROR\n";
        return; //ACA VA EXCEPION
    }
    map_file >> json_map_file;

    std::ifstream tiles_file(this->map_paths + (std::string)json_map_file["tilesets"][0]["source"]);
    if (!tiles_file.is_open()) {
        std::cerr << "MAP TILE ERROR\n";
        return; //ACA VA EXCEPION
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

bool is_track(int32_t type_ID) {
    return (type_ID >= 0 && type_ID <= 27) ||
           (type_ID >= 29 && type_ID <= 55) ||
           (type_ID >= 63 && type_ID <= 89);
}

void set_track_to_race(std::vector<std::unique_ptr<Terrain>>& track, RacingTrack& racing_track) {
    for (auto& track_part : track) {
        racing_track.add_track(std::move(track_part));
    }
}

void MapLoader::load_map(RacingTrack &racing_track, const std::string& map_filename) {
    json json_map_data;
    json json_tiles_data;
    this->open_files(json_map_data, json_tiles_data, map_filename);

    int map_width = json_map_data["width"];
    int map_height = json_map_data["height"];

    racing_track.set_track_size(map_height, map_width);
    racing_track.set_track_terrain(TYPE_GRASS);

    std::unique_ptr<Terrain> begin_tile(nullptr);

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {

            unsigned ID_pos =
                    unsigned(json_map_data["layers"][FIRST_LAYER]["data"][j * (int) json_map_data["height"] + i]) - 1;
            int32_t type_ID = json_tiles_data["tiles"][ID_pos]["properties"][ID_PROPERTY_POS]["value"];

            int32_t tile_rotation = json_tiles_data["tiles"][ID_pos]["properties"][ROTATION_PROPERTY_POS]["value"];
            bool is_static = json_tiles_data["tiles"][ID_pos]["properties"][STATIC_PROPERTY_POS]["value"];

            if (is_static)
                racing_track.add_static_track_object(std::move(StaticTrackObject(type_ID, i, j, tile_rotation)));
            else {
                if (is_track(type_ID) && type_ID == BEGIN_TRACK_TILE)
                    begin_tile = std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation));
                else if (is_track(type_ID) & ((type_ID == TYPE_FINISH_LINE_BORDER) || (type_ID == TYPE_FINISH_LINE_CENTER)))
                    racing_track.add_track((std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation))));
                else if (is_track(type_ID))
                    this->track.push_back((std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation))));
                else
                    racing_track.add_terrain(std::move(TerrainFactory::create_terrain(type_ID, i, j, tile_rotation)));
            }

            this->add_tile_behaviour(type_ID, i, j, tile_rotation, racing_track);
        }
    }

    this->track.push_back(std::move(begin_tile));
    this->generate_track_graph();
    set_track_to_race(this->track, racing_track);

    if (finish_line.size() == 2) racing_track.set_finish_line(finish_line[0], finish_line[1]);
    if (podium.size() == 3) racing_track.set_podium(podium.at(1), podium.at(2), podium.at(3));
}


bool are_adjacent(std::unique_ptr<Terrain>& t_a, std::unique_ptr<Terrain>& t_b) {
    Coordinate a = t_a->get_map_coordinate();
    Coordinate b = t_b->get_map_coordinate();
    return  a.is_adjacent_to(b);
}

void MapLoader::generate_track_graph() {
    std::vector<std::vector<int32_t> > graph(this->track.size());

    for (size_t row = 0; row < this->track.size(); row++) {
        for (auto &col : this->track) {
            if (are_adjacent(this->track[row], col))
                graph[row].emplace_back(1);
            else
                graph[row].emplace_back(0);
        }
    }

    std::vector<int32_t> distances(this->track.size());
    size_t source_pos = this->track.size() - 1;
    Dijkstra::dijkstra(graph, distances, source_pos);

    for (size_t i = 0; i < distances.size(); i++) {
        this->track[i]->set_begin_distance(distances[i]);
    }

}

