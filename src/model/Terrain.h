#ifndef MICROMACHINES_TERRAIN_H
#define MICROMACHINES_TERRAIN_H

#include <cstdint>
#include <server/UpdateClient.h>

class Terrain {

    protected:
        int32_t map_x;
        int32_t map_y;
        int32_t rotation;

    public:
        Terrain(int32_t x, int32_t y, int32_t rotation);

        virtual UpdateClient get_to_send() = 0;
};


#endif //MICROMACHINES_TERRAIN_H
