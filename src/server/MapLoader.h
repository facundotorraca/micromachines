#ifndef MICROMACHINES_MAPLOADER_H
#define MICROMACHINES_MAPLOADER_H

#include <list>
#include <string>
#include <model/Terrains/Grass.h>
#include <model/RacingTrack.h>

class MapLoader {

    std::string map_paths;
    int32_t map_withd;
    int32_t map_heigth;

    public:
        explicit MapLoader(std::string map_path);

        void load_map(RacingTrack& racing_track, const std::string& map_filename, const std::string& tiles_filename);

    UpdateClient get_info_to_send();
};


#endif //MICROMACHINES_MAPLOADER_H
