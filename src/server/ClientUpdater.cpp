#include "ClientUpdater.h"

void ClientUpdater::create_update_queue(int32_t ID, size_t max_size) {
    this->updates_players.emplace(ID, 15000/*queue len*/);
}

UpdateClient ClientUpdater::get_update(int32_t ID) {
    return this->updates_players.at(ID).pop();
}

void ClientUpdater::close_queue(int32_t ID) {
    this->updates_players.at(ID).close();
}

void ClientUpdater::send_to_all(UpdateClient update) {
    for (auto& queue : this->updates_players) {
        queue.second.push(update);
    }
}

void ClientUpdater::send_to(int32_t ID, UpdateClient update) {
    this->updates_players.at(ID).push(update);
}

void ClientUpdater::remove_queue(int32_t ID) {
    this->updates_players.erase(ID);
}