#include <random>
#include <iostream>
#include "ModifierSpawner.h"
#include <common/MsgTypes.h>
#include <model/RacingTrack.h>
#include <common/Sizes.h>
#include <common/EntityType.h>

#define MUD_PROB 0.2
#define OIL_PROB 0.2
#define FIX_PROB 0.2
#define ROCK_PROB 0.2
#define BOOST_PROB 0.2

#define TIME_OF_LIFE 6000 //10 sec

static double get_uniform_number() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(mt);
}

ModifierSpawner::ModifierSpawner(float probability, RacingTrack &racing_track):
    racing_track(racing_track),
    factory(ModifierProbability{MUD_PROB, OIL_PROB, FIX_PROB, ROCK_PROB, BOOST_PROB} )
{
    this->probability = probability;
}

void ModifierSpawner::send_modifiers_update(ClientUpdater& updater) {
    double number = get_uniform_number();

    if (number < this->probability) {
        this->try_spawn_modifier(updater);
    } else {
        this->try_despawn_modifier(updater);
    }
}

void ModifierSpawner::update() {
    for (auto& modifier : this->spawned_modifiers) {
        modifier->update_remaining_life();
    }
}

void ModifierSpawner::try_despawn_modifier(ClientUpdater& updater) {
    for (auto modifier = this->spawned_modifiers.begin(); modifier != this->spawned_modifiers.end();) {
        if ((*modifier)->is_dead()) {
            Coordinate dead_modifier_pos = (*modifier)->get_coordinate();

            int32_t x_upd = (dead_modifier_pos.get_x() * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;
            int32_t y_upd = (dead_modifier_pos.get_y() * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;

            modifier = this->spawned_modifiers.erase(modifier);
            updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_REMOVE_MODIFIER, x_upd, y_upd}));
        } else {
            modifier++;
        }
    }
}

void ModifierSpawner::try_spawn_modifier(ClientUpdater& updater) {
    Coordinate modifier_spawn_pos = this->racing_track.get_random_track_position();

    float x_map = modifier_spawn_pos.get_x();
    float y_map = modifier_spawn_pos.get_y();

    std::shared_ptr<Modifier> modifier = this->factory.get_modifier_randomly(TIME_OF_LIFE, x_map, y_map);
    this->racing_track.add_modifier(modifier);

    int32_t modifier_type = modifier->get_modifier_type();
    this->spawned_modifiers.emplace_back(std::move(modifier));

    int32_t x_upd = (x_map * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;
    int32_t y_upd = (y_map * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;

    updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_ADD_MODIFIER, modifier_type, x_upd, y_upd}));
}
