#ifndef MICROMACHINES_MAPLOADER_H
#define MICROMACHINES_MAPLOADER_H

#include <list>
#include <string>
#include <unordered_map>
#include "json/json.hpp"
#include <common/Coordinate.h>
#include <model/Vehicle/Car.h>
#include <model/Terrains/Terrain.h>

class RacingTrack;

class MapLoader {

    std::string map_name;
    std::string map_paths;

    std::vector<Coordinate> finish_line;
    std::vector<std::unique_ptr<Terrain>> track;
    std::unordered_map<int32_t, Coordinate> podium;

    private:
        void generate_track_graph();

        void orientate_track(nlohmann::json& map_file, nlohmann::json& tiles_file);

        void open_files(nlohmann::json& map_file, nlohmann::json& tiles_file);

        void add_tile_behaviour(int32_t type_ID, int32_t i, int32_t j, int32_t rot, RacingTrack& racingTrack);

    public:
        explicit MapLoader(std::string map_path, std::string map_name);

        void load_map(RacingTrack& racing_track, ClientUpdater& updater);
};

#endif //MICROMACHINES_MAPLOADER_H
