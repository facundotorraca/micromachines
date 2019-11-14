#ifndef MICROMACHINES_MODIFIERSPAWNER_H
#define MICROMACHINES_MODIFIERSPAWNER_H

#include "Modifier.h"
#include <unordered_map>
#include "ModifierFactory.h"
#include <model/RacingTrack.h>
#include <common/Coordinate.h>

class ModifierSpawner {

    float probability;

    ModifierFactory factory;

    RacingTrack& racing_track;

    std::vector<std::shared_ptr<Modifier>> spawned_modifiers;
    std::vector<std::shared_ptr<Modifier>> pit_stop_modifiers;

    private:
        void reload_pit_stop(ClientUpdater& updater);

        void try_spawn_modifier(ClientUpdater& updater);

        void try_despawn_modifier(ClientUpdater& updater);

        std::shared_ptr<Modifier> generate_fix_or_boost_modifier(ClientUpdater& updater, Coordinate coordinate);

    public:
        ModifierSpawner(float probability, RacingTrack& racing_track);

        void send_modifiers_update(ClientUpdater& updater);

        void update();
};


#endif //MICROMACHINES_MODIFIERSPAWNER_H
