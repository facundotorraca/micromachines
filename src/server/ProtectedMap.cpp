#include "ProtectedMap.h"
#include <mutex>
#include <list>
#include <map>
#include <iostream>

void ProtectedMap::add(const std::string& match_name, Match* match) {
    std::lock_guard<std::mutex> lock(this->mtx);
    if (!this->map.insert(std::pair<std::string, Match*>(match_name, match)).second) {
        std::cout << "error" << "\n";
    }
    std::cout << this->map.size() <<"\n";
}

Match* ProtectedMap::get(const std::string& match_name) {
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
/*Esta funcion esta medio hardcodeada*/
void ProtectedMap::send_matches(Socket &socket) {
    for (auto it = this->map.begin(); it != this->map.end(); it++) {
        std::string match_name = (*it).second->get_match_name();
        uint8_t len_match_name = match_name.length();

        socket.send(&len_match_name, 1);
        socket.send((uint8_t*)match_name.data(), match_name.length());
    }
    uint8_t end_byte = '\0';
    uint8_t len_end_byte = 1;

    socket.send(&len_end_byte, 1);
    socket.send(&end_byte, 1);
}






