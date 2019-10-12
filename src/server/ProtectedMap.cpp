#include "ProtectedMap.h"
#include <mutex>
#include <list>
#include <map>
#include <iostream>

void ProtectedMap::add(std::string match_name, Match* match) {
    std::lock_guard<std::mutex> lock(this->mtx);
    if (!this->map.insert(std::pair<std::string, Match*>(match_name, match)).second) {
        std::cout << "error" << "\n";
    }
    std::cout << this->map.size() <<"\n";
}

Match* ProtectedMap::get(std::string match_name) {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->map[match_name];
}

void ProtectedMap::remove_end_matches() {
    std::lock_guard<std::mutex> lock(this->mtx);
    for (auto it = this->map.begin(); it != this->map.end();) {
        if ((*it).second->ended()) {
            it = this->map.erase(it);
        } else {
            it++;
        }
    }
}






