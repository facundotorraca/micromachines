#ifndef MICROMACHINES_ASPHALT_H
#define MICROMACHINES_ASPHALT_H

#include "Terrain.h"

class Asphalt : public Terrain {

    public:
        Asphalt(int32_t x, int32_t y, int32_t rotation);

        UpdateClient get_to_send() override;

};


#endif //MICROMACHINES_ASPHALT_H
