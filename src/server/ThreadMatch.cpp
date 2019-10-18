#include <thread>
#include <chrono>
#include <iostream>
#include "ThreadMatch.h"
#include <common/EntityType.h>
#include <common/MsgTypes.h>

ThreadMatch::ThreadMatch(std::shared_ptr<Match>&& match):
    match(std::move(match)),
    dead(false)
{}

void ThreadMatch::run() {
    this->match->run();

    bool a = true;
    int32_t i = 0;

    std::vector<int32_t> hola{MSG_CAR_ID, 1};
    std::vector<int32_t> track{MSG_MAP, 1};
    this->match->send_to_all(hola);
    this->match->send_to_all(track);
    while (!dead)  {
        i+=3;
        std::vector<int32_t> chau{MSG_UPDATE_ENTITY, 2, TYPE_CAR, 30, 10, 30};
        std::vector<int32_t> hola2{MSG_UPDATE_ENTITY, 1, TYPE_CAR, i, 100, 0};
        this->match->send_to_all(hola2);
        this->match->send_to_all(chau);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
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
