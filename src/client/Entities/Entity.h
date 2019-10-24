#ifndef MICROMACHINES_ENTITY_H
#define MICROMACHINES_ENTITY_H

#include <cstdint>
#include <client/Camera.h>

class Entity {
    protected:
        int posX = 0;
        int posY = 0;
        int rot = 0;
    public:
        virtual void draw(Camera& camera) = 0;
        virtual void update_position(int32_t px, int32_t py, int32_t r) {
            this->posX = px;
            this->posY = py;
            this->rot = r;
        }
};


#endif //MICROMACHINES_ENTITY_H
