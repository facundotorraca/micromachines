#include <iostream>
#include "ThreadMatch.h"

#include <thread>
#include <chrono>

ThreadMatch::ThreadMatch(Match *match):
    dead(false)
{
    this->match = match;
}

void ThreadMatch::run() {
    std::string hola("hello");

    bool a = true;
    while (a)  {
        this->match->send_to_all(hola);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    this->match->stop();
    this->dead = true;
}

bool ThreadMatch::is_running() {
    return !this->dead;
}
