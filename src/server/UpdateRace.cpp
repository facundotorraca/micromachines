#include <map>
#include <string>
#include "model/Car.h"
#include "UpdateRace.h"

UpdateRace::UpdateRace(int32_t client_ID, uint8_t key, uint8_t key_state) {
    this->key = key;
    this->client_ID = client_ID;
    this->key_state = key_state;
}

void UpdateRace::update_cars(std::map<uint8_t, Car>& cars) {
    if (this->key_state == KEY_PRESSED) {
        cars.at(this->client_ID).press_key(key);
    } else {
        cars.at(this->client_ID).release_key(key);
    }
}
