#include <iostream>
#include <server/UpdateClient.h>
#include <common/MsgTypes.h>
#include "CarLife.h"

CarLife::CarLife(float max_life) {
    this->life = max_life;
    this->max_life = max_life;
}

void CarLife::make_damage(float damage) {
    this->life = this->life - damage;
    std::cout << this->life << "\n";
}

bool CarLife::is_dead() {
    return this->life <= 0;
}

void CarLife::restart_life() {
    this->life = this->max_life;
    std::cout << "LIFE RESTARTED: " << this->life << "\n";
}

UpdateClient CarLife::get_life_update(int32_t ID) {
    return UpdateClient({MSG_SET_HEALTH, ID, int32_t(this->life) });
}
