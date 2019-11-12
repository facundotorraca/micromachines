#include <iostream>
#include <server/UpdateClient.h>
#include <common/MsgTypes.h>
#include <model/DTO_Info.h>
#include "CarLife.h"

CarLife::CarLife(float max_life):
    changed(false)
{
    this->life = max_life;
    this->max_life = max_life;
}

void CarLife::make_damage(float damage) {
    this->life = this->life - damage;
    this->changed = true;
}

bool CarLife::is_dead() {
    return this->life <= 0;
}

void CarLife::restart_life() {
    this->life = this->max_life;
    this->changed = true;
}

void CarLife::send_updates(int32_t ID, ClientUpdater &updater) {
    if (this->changed) {
        updater.send_to_all(UpdateClient(std::vector<int32_t>{MSG_SET_HEALTH, ID, int32_t(this->life)} ));
        this->changed = false;
    }
}

void CarLife::get_dto_info(DTO_CarLife& info_life) {
    info_life.max_life = this->max_life;
    info_life.current_life = this->life;
}

void CarLife::apply_plugin(DTO_CarLife &life_info) {
    this->max_life = life_info.max_life;
    this->life = life_info.current_life;
    this->changed = true;
}

void CarLife::kill() {
    this->life = 0;
    this->changed = true;
}
