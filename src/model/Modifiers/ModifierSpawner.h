#ifndef MICROMACHINES_MODIFIERSPAWNER_H
#define MICROMACHINES_MODIFIERSPAWNER_H

#include "Modifier.h"
#include "ModifierFactory.h"
#include <model/RacingTrack.h>

class ModifierSpawner {

    float probability;

    ModifierFactory factory;

    RacingTrack& racing_track;
    std::vector<std::unique_ptr<Modifier>> spawned_modifiers;

    private:
        void try_spawn_modifier(ClientUpdater& updater);

        void try_despawn_modifier(ClientUpdater& updater);

    public:
        ModifierSpawner(float probability, RacingTrack& racing_track);

        void get_update_modifiers(ClientUpdater& updater);

        void update();
};


#endif //MICROMACHINES_MODIFIERSPAWNER_H
