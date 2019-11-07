#ifndef MICROMACHINES_MODIFIERFACTORY_H
#define MICROMACHINES_MODIFIERFACTORY_H

#include <memory>
#include "Modifier.h"
#include "ModifierProbability.h"

class ModifierFactory {

    ModifierProbability probability;

    public:
        explicit ModifierFactory(ModifierProbability probability);

        std::shared_ptr<Modifier> get_modifier_randomly(int32_t time_of_life, int32_t map_x, int32_t map_y);


};




#endif //MICROMACHINES_MODIFIERFACTORY_H
