#include "ThreadMatch.h"
#include <vector>
#include <iostream>
#include "Player.h"

ThreadMatch::ThreadMatch(ProtectedList* lobby):
    lobby(lobby)
{}

void ThreadMatch::start() {
    this->thread = std::thread(&ThreadMatch::run, this);
}

void ThreadMatch::run() {
    bool a = true;
    size_t size = 0;
    while (a) {
        if (size != this->lobby->size()) {
            size = this->lobby->size();
            Player *player = this->lobby->back();
            std::string a("hello");
            player->send(a);
        }
    }
}
