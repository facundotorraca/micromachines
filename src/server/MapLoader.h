#ifndef MICROMACHINES_MAPLOADER_H
#define MICROMACHINES_MAPLOADER_H

#include <list>
#include <string>
#include <model/Grass.h>
#include <model/RacingTrack.h>

class MapLoader {

    std::string map_paths;

    public:
        explicit MapLoader(std::string map_path);

        void load_map(RacingTrack& racing_track, const std::string& map_filename, const std::string& tiles_filename);

};


#endif //MICROMACHINES_MAPLOADER_H
