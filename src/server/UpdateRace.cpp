#include <map>
#include <string>
#include "Player.h"
#include "UpdateRace.h"
#include "model/Vehicle/Car.h"

UpdateRace::UpdateRace(int32_t client_ID, int32_t key, int32_t key_state) {
    this->key = key;
    this->client_ID = client_ID;
    this->key_state = key_state;
}

void UpdateRace::update_cars(std::unordered_map<int32_t, Car>& cars) {
    if (this->key_state == KEY_PRESSED) {
        cars.at(this->client_ID).move(key);
    } else /*KEY_UNPRESSED*/ {
        cars.at(this->client_ID).stop(key);
    }
}

void UpdateRace::update_player_view(std::unordered_map<int32_t, Player>& players) {
    if (this->key_state == KEY_PRESSED && (this->key == TURN_LEFT || this->key == TURN_RIGHT))
        players.at(this->client_ID).set_view(this->key);
}
