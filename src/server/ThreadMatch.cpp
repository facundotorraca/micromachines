#include <thread>
#include <chrono>
#include <iostream>
#include "ThreadMatch.h"
#include <common/EntityType.h>

ThreadMatch::ThreadMatch(std::shared_ptr<Match>&& match):
    match(std::move(match)),
    dead(false)
{}

void ThreadMatch::run() {
    this->match->run();

    bool a = true;
    uint8_t i = 0;
    while (!dead)  {
        i++;
        std::vector<uint8_t> hola{1, TYPE_CAR, i, 100, 0};
        std::vector<uint8_t> chau{2, TYPE_CAR, 30, 10, 30};
        this->match->send_to_all(hola);
        this->match->send_to_all(chau);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    this->match->stop();
    this->dead = true;
}

bool ThreadMatch::is_running() {
    return !this->dead;
}

void ThreadMatch::stop() {
    this->dead = true;
}
