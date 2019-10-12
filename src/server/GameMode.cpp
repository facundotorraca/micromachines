#include "GameMode.h"
#include <string>
#include <utility>

#define JOIN_MODE 1
//#define CREATE_MODE 2

GameMode::GameMode(uint8_t mode) {
    this->mode = mode;
}

bool GameMode::is_join() {
    return mode == JOIN_MODE;
}
