#include <vector>
#include <iostream>
#include "LapCounter.h"
#include <common/MsgTypes.h>
#include <server/UpdateClient.h>
#include <server/ClientUpdater.h>

LapCounter::LapCounter(int32_t total_laps):
    total_laps(total_laps)
{}

void LapCounter::add_lap(int32_t ID) {
    try {
        this->laps.at(ID)++;
    } catch(const std::out_of_range &e) {
        /*first appearance of the car*/
        this->laps[ID] = 1;
    }
}

void LapCounter::take_lap(int32_t ID) {
    try {
        if (this->laps.at(ID) >= 1)
            this->laps.at(ID)--;
    } catch(const std::out_of_range &e) {
        std::cerr << "ERROR ID: Car not loaded\n";
    }
}

bool LapCounter::car_complete_laps(int32_t ID) {
    try {
        return this->laps.at(ID) > this->total_laps;
    } catch (const std::out_of_range &e) {
        return false;
    }
}

int32_t LapCounter::get_total_laps() {
    return this->total_laps;
}

void LapCounter::send_update(int32_t ID, ClientUpdater& client_updater) {
    try {
        int32_t player_laps = this->laps.at(ID);
        client_updater.send_to(ID, UpdateClient(std::vector<int32_t>{MSG_SET_LAP, player_laps}));
    } catch (const std::out_of_range &e) {
        client_updater.send_to(ID, UpdateClient(std::vector<int32_t>{MSG_SET_LAP, 0}));
    }
}
