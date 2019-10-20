#ifndef MICROMACHINES_WHEEL_H
#define MICROMACHINES_WHEEL_H

#include "Entity.h"

class Wheel : public Entity {
public:
    explicit Wheel(SDL_Renderer* r);
    void draw(SDL_Point camera) override;
    void update_all(std::vector<int32_t>& update_info) override {};
};


#endif //MICROMACHINES_WHEEL_H
