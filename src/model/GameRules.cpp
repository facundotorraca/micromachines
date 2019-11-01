#include <iostream>
#include "GameRules.h"

#define INVALID_ID -1

GameRules::GameRules(int32_t total_laps) :
    total_laps(total_laps),
    finished(false),
    laps(),
    positions()
{}

bool GameRules::add_lap(int32_t id) {
    try {
        this->laps.at(id);
        this->laps[id]++;
    } catch(const std::out_of_range &e) {
        this->laps[id] = 0;
    }
    if (this->laps[id] == this->total_laps) {
        this->positions.push_back(id);
    }
    return false;
}

void GameRules::take_lap(int32_t id) {
    try {
        if (this->laps.at(id) >= 1)
            this->laps[id]--;
    } catch(const std::out_of_range &e) {
        std::cerr << "ERROR ID \n";
    }
}

bool GameRules::is_finished() {
    return this->laps.size() == this->positions.size();
}

int32_t GameRules::get_winner() {
    if (this->positions.empty())
        return INVALID_ID;
    return this->positions[0];
}

int32_t GameRules::get_lap(int32_t id) {
    try {
        return this->laps.at(id);
    } catch (std::out_of_range &e) {
        return 0;
    }
}

void GameRules::get_update(int32_t id) {
    std::cout << "LAP: " << this->laps[id] << "/" << this->total_laps << std::endl;
}


GameRules::~GameRules() = default;