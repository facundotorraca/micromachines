#include "ProtectedList.h"
#include "Player.h"
#include <mutex>
#include <list>

void ProtectedList::append(Player* player) {
    std::lock_guard<std::mutex> lock(this->mtx);
    this->list.push_back(player);
}

size_t ProtectedList::size() {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->list.size();
}

Player *ProtectedList::back() {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->list.back();
}
