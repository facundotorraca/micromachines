#include "ProtectedMap.h"
#include "Player.h"
#include <vector>
#include <mutex>
#include <map>

void ProtectedMap::add(std::string match_name, ProtectedList* lobby) {
    std::lock_guard<std::mutex> lock(this->mtx);
    this->map.insert(std::pair<std::string, ProtectedList*>(match_name, lobby));

}

ProtectedList* ProtectedMap::get(std::string match_name) {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->map[match_name];
}
