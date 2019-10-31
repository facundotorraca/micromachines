#include <memory>
#include <iostream>
#include "server/MatchTable.h"
#include "ThreadMatchStarter.h"
#include "common/ProtectedQueueError.h"

ThreadMatchStarter::ThreadMatchStarter(MatchTable& matches, std::list<std::shared_ptr<Match>>& running_matches, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches):
    not_ready_matches(not_ready_matches),
    running_matches(running_matches),
    server_running(true),
    matches(matches)
{}

void ThreadMatchStarter::close_ended_matches() {
    for (auto running_match = this->running_matches.begin(); running_match != this->running_matches.end();) {
        if (!(*running_match)->is_runnig()) {
            (*running_match)->join();
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
            std::shared_ptr<Match> new_running_match = this->not_ready_matches.pop();
            new_running_match->start();
            this->running_matches.push_back(new_running_match);
            this->close_ended_matches();
        } catch (ProtectedQueueError& exception) {
            this->server_running = false;
        }
    }
}

