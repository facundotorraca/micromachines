#include "GameMode.h"
#include <string>
#include <utility>

#define JOIN_MODE 1
//#define CREATE_MODE 2

GameMode::GameMode(uint8_t mode, std::string match_name) {
    this->mode = mode;
    this->match_name = std::move(match_name);
}

bool GameMode::is_join() {
    return mode == JOIN_MODE;
}

std::string GameMode::get_match_name() {
    return this->match_name;
}
