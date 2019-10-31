#include "GameRules.h"

GameRules::GameRules(uint32_t total_laps) : total_laps(total_laps),
                                            finished(false),
                                            laps(),
                                            positions() {}

bool GameRules::add_lap(uint32_t id) {
    try {
        this->laps.at(id);
        this->laps[id]++;
    } catch(const std::out_of_range &e) {
        this->laps[id] = 0;
    }
    if (this->laps[id] == this->total_laps) {
        this->positions.push_back(id);
        return true;
    }
    return false;
}

bool GameRules::is_finished() {
    return this->laps.size() == this->positions.size();
}

int32_t GameRules::get_winner() {
    if (this->positions.empty())
        return INVALID_ID;
    return this->positions[0];
}

uint32_t GameRules::get_lap(uint32_t id) {
    try {
        return this->laps.at(id);
    } catch (std::out_of_range &e) {
        return 0;
    }
}

GameRules::~GameRules() {}