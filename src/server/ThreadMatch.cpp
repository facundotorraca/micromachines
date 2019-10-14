#include <thread>
#include <chrono>
#include <iostream>
#include "ThreadMatch.h"

ThreadMatch::ThreadMatch(std::shared_ptr<Match>&& match):
    match(std::move(match)),
    dead(false)
{}

void ThreadMatch::run() {
    this->match->run();
    std::string hola("hello");

    bool a = true;
    while (!dead)  {
        this->match->send_to_all(hola);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
