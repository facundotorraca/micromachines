//
// Created by javier on 6/11/19.
//

#ifndef MICROMACHINES_ENTITIES_H
#define MICROMACHINES_ENTITIES_H

#include "Camera.h"
#include <unordered_map>

struct Modifier{
    int32_t type;
    int32_t x;
    int32_t y;
};

class ModifiersContainer {
    std::unordered_map<int64_t, Modifier> modifiers;
public:
    ModifiersContainer();
    void addModifier(int32_t type, int32_t x, int32_t y);
    void removeModifier(int32_t x, int32_t y);
    void draw(Camera& camera);
};


#endif //MICROMACHINES_ENTITIES_H
