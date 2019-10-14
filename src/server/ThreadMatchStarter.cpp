#include <memory>
#include <iostream>
#include "server/MatchTable.h"
#include "ThreadMatchStarter.h"
#include "server/ProtectedQueueError.h"

ThreadMatchStarter::ThreadMatchStarter(MatchTable& matches, std::list<ThreadMatch *>& running_matches, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches):
    not_ready_matches(not_ready_matches),
    running_matches(running_matches),
    server_running(true),
    matches(matches)
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

void ThreadMatchStarter::stop() {
    this->not_ready_matches.close();
}


void ThreadMatchStarter::run() {
    while (this->server_running) {
        try {
            std::shared_ptr<Match> match = this->not_ready_matches.pop();
            auto* new_running_match = new ThreadMatch(std::move(match));
            this->running_matches.push_back(new_running_match);
            new_running_match->start();
            this->close_ended_matches();
        } catch (ProtectedQueueError& exception) {
            this->server_running = false;
        }

    }
}
