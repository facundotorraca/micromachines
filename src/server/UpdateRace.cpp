#include <map>
#include <string>
#include "Player.h"
#include "UpdateRace.h"
#include <model/Race.h>
#include "model/Vehicle/Car.h"
#include "Match.h"

UpdateRace::UpdateRace(int32_t client_ID, int32_t key, int32_t key_state) {
    this->key = key;
    this->client_ID = client_ID;
    this->key_state = key_state;
}

void UpdateRace::update_cars(std::unordered_map<int32_t, Car>& cars) {
    try {
        if (this->key_state == KEY_PRESSED) {
            cars.at(this->client_ID).move(key);
        } else /*KEY_UNPRESSED*/ {
            cars.at(this->client_ID).stop(key);
        }
    } catch (const std::out_of_range &e) {}
}

void UpdateRace::update_player_view(std::unordered_map<int32_t, Player>& players) {
    try {
        if (this->key_state == KEY_PRESSED && (this->key == TURN_LEFT || this->key == TURN_RIGHT))
            players.at(this->client_ID).set_view(this->key);
    } catch (const std::out_of_range &e) {}
}

bool UpdateRace::apply_restart_option(Race &race, std::unordered_map<int32_t, Player>& players,  Match* match) {
    if (this->key_state == KEY_PRESSED && this->key == KEY_RESTART) {
        match->restart_match();
        race.restart();
        return true;
    }
    if (this->key_state == KEY_PRESSED && this->key == KEY_QUIT) {
        for (auto& player : players)
            player.second.kill();
        return true;
    }
    return false;
}

bool UpdateRace::is_from(int32_t ID) {
    return this->client_ID == ID;
}
