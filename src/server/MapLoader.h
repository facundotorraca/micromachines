#ifndef MICROMACHINES_MAPLOADER_H
#define MICROMACHINES_MAPLOADER_H

#include <list>
#include <string>
#include <unordered_map>
#include <model/RacingTrack.h>
#include <common/Coordinate.h>
#include <model/Vehicle/Car.h>

class MapLoader {

    std::string map_paths;
    std::vector<Coordinate> spawn_points;

public:
    explicit MapLoader(std::string map_path);

    void set_cars_spawn_point(std::unordered_map<int32_t, Car>& cars);

    void load_map(RacingTrack& racing_track, const std::string& map_filename, const std::string& tiles_filename);
};

#endif //MICROMACHINES_MAPLOADER_H
