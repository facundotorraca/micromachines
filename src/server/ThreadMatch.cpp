#include "ThreadMatch.h"

ThreadMatch::ThreadMatch(Match *match):
    dead(false)
{
    this->match = match;
}

void ThreadMatch::run() {
    std::string hola("hello");
    this->match->send_to_all(hola);
    this->match->stop();
    this->dead = true;
}

bool ThreadMatch::is_running() {
    return this->dead;
}
