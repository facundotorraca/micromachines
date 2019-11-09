#ifndef MICROMACHINES_MAPLOADER_H
#define MICROMACHINES_MAPLOADER_H

#include <list>
#include <string>
#include <unordered_map>
#include "json/json.hpp"
#include <model/RacingTrack.h>
#include <common/Coordinate.h>
#include <model/Vehicle/Car.h>

class MapLoader {

    std::string map_paths;
    std::vector<Coordinate> finish_line;
    std::vector<int32_t> track_distances;
    std::vector<std::unique_ptr<Terrain>> track;
    std::unordered_map<int32_t, Coordinate> podium;

    private:
        void generate_track_graph();

        void open_files(nlohmann::json& map_file, nlohmann::json& tiles_file, const std::string& map_filename);

        void add_tile_behaviour(int32_t type_ID, int32_t i, int32_t j, int32_t rot, RacingTrack& racingTrack);

    public:
        explicit MapLoader(std::string map_path);

        void load_map(RacingTrack& racing_track, const std::string& map_filename);
};

#endif //MICROMACHINES_MAPLOADER_H
