#include <iostream>
#include "ProtectedMap.h"
#include "ThreadMatchStarter.h"

#include <chrono>
#include <thread>

ThreadMatchStarter::ThreadMatchStarter(ProtectedMap& matches, std::list<ThreadMatch *>& running_matches):
    matches(matches),
    running_matches(running_matches),
    server_running(true)
{}

void ThreadMatchStarter::close_ended_matches() {
    for (auto running_match = this->running_matches.begin(); running_match != this->running_matches.end();) {
        if (!(*running_match)->is_running()) {
            (*running_match)->join();
            delete (*running_match);
            running_match = running_matches.erase(running_match);
        } else {
            running_match++;
        }
    }
    this->matches.remove_end_matches();
}

void ThreadMatchStarter::run() {
    while (this->server_running) {
        Match* match = this->matches.get_next_ready();
        if (match) {
            match->run();
            auto* new_running_match = new ThreadMatch(match);
            this->running_matches.push_back(new_running_match);
            new_running_match->start();
        }
        this->close_ended_matches();
    }
}
