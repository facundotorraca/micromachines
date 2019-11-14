#include <random>
#include <unordered_map>
#include <common/Sizes.h>
#include <common/Configs.h>
#include "ModifierSpawner.h"
#include <common/MsgTypes.h>
#include <model/RacingTrack.h>

#define TIME_OF_LIFE 100 //20 sec

static double get_uniform_number() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(mt);
}

int32_t get_scaled_value(int32_t axis) {
    return (axis * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;
}

ModifierSpawner::ModifierSpawner(float probability, RacingTrack &racing_track):
    racing_track(racing_track),
    factory(ModifierProbability{Configs::get_configs().mod_mud_prob,
                                          Configs::get_configs().mod_oil_prob,
                                          Configs::get_configs().mod_fix_prob,
                                          Configs::get_configs().mod_rock_prob,
                                          Configs::get_configs().mod_boost_prob} )
{
    this->probability = probability;
}

void ModifierSpawner::send_modifiers_update(ClientUpdater& updater) {
    double number = get_uniform_number();

    if (number < this->probability) {
        this->reload_pit_stop(updater);
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

            int32_t x_upd = get_scaled_value(dead_modifier_pos.get_x());
            int32_t y_upd = get_scaled_value(dead_modifier_pos.get_y());

            modifier = this->spawned_modifiers.erase(modifier);
            updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_REMOVE_MODIFIER, x_upd, y_upd}));
        } else {
            modifier++;
        }
    }

    for (auto& modifier : this->pit_stop_modifiers) {
        if (modifier->is_dead()) {
            Coordinate dead_modifier_pos = modifier->get_coordinate();

            int32_t x_upd = get_scaled_value(dead_modifier_pos.get_x());
            int32_t y_upd = get_scaled_value(dead_modifier_pos.get_y());
            updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_REMOVE_MODIFIER, x_upd, y_upd}));
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

    int32_t x_upd = get_scaled_value(x_map);
    int32_t y_upd = get_scaled_value(y_map);

    updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_ADD_MODIFIER, modifier_type, x_upd, y_upd}));
}


std::shared_ptr<Modifier> ModifierSpawner::generate_fix_or_boost_modifier(ClientUpdater &updater, Coordinate coordinate) {
    float x_map = coordinate.get_x();
    float y_map = coordinate.get_y();

    std::shared_ptr<Modifier> modifier = ModifierFactory::get_life_or_boost(TIME_OF_LIFE, x_map, y_map);
    this->racing_track.add_modifier(modifier);

    int32_t modifier_type = modifier->get_modifier_type();
    int32_t x_upd = get_scaled_value(x_map);
    int32_t y_upd = get_scaled_value(y_map);

    updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_ADD_MODIFIER, modifier_type, x_upd, y_upd}));
    return modifier;
}

void ModifierSpawner::reload_pit_stop(ClientUpdater& updater) {
    std::vector<Coordinate>& pit_stop = this->racing_track.get_pit_stop_position();

    if (this->pit_stop_modifiers.empty()) {
        for (auto &coordinate: pit_stop) {
            std::shared_ptr<Modifier> new_modifier = generate_fix_or_boost_modifier(updater, coordinate);
            this->pit_stop_modifiers.emplace_back(std::move(new_modifier));
        }
    } else {
        for (size_t i = 0; i < this->pit_stop_modifiers.size(); i++) {
            if (pit_stop_modifiers[i]->is_dead()) {
                Coordinate coord = pit_stop_modifiers[i]->get_coordinate();
                std::shared_ptr<Modifier> new_modifier = generate_fix_or_boost_modifier(updater, coord);
                this->pit_stop_modifiers.at(i) = std::move(new_modifier);
            }
        }
    }

}
