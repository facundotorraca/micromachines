#include <list>
#include <memory>
#include <iostream>
#include "server/Match.h"
#include "server/Player.h"
#include "server/MatchTable.h"
#include "common/ProtectedQueue.h"
#include "ThreadPlayerLocator.h"
#include "common/ProtectedQueueError.h"

ThreadPlayerLocator::ThreadPlayerLocator(ProtectedQueue<Player>& incoming_players, MatchTable &matches, ProtectedQueue<std::shared_ptr<Match>>& not_read_matches):
    not_ready_matches(not_read_matches),
    incoming_players(incoming_players),
    server_running(true),
    matches(matches)
{}

void ThreadPlayerLocator::remove_running_matches() {
    for (auto setter = this->options_setters.begin(); setter != this->options_setters.end();) {
        if ((*setter)->options_set()) {
            (*setter)->join();
            delete (*setter);
            setter = options_setters.erase(setter);
        } else {
            setter++;
        }
    }
}

void ThreadPlayerLocator::stop() {
    this->incoming_players.close();
}

void ThreadPlayerLocator::kill_all_setter() {
    for (auto & setter : this->options_setters) {
        setter->stop();
    }
}

void ThreadPlayerLocator::run() {
    while (this->server_running) {
        try {
            Player new_player = this->incoming_players.pop();

            if (new_player.is_on_join_mode()) {
                std::shared_ptr<Match> match = this->matches.get(new_player.get_match_name());
                match->add_player(std::move(new_player));
            } else {
                std::shared_ptr<Match> new_match(new Match(new_player.get_username(), new_player.get_match_name()));
                this->matches.add(new_player.get_match_name(), new_match);

                auto* setter = new ThreadMatchOptions(std::move(new_player), std::move(new_match), this->not_ready_matches);
                this->options_setters.push_back(setter);
                setter->start();
            }

            this->remove_running_matches();
        } catch (const ProtectedQueueError &exception) {
            this->kill_all_setter();
            this->remove_running_matches();
            this->server_running = false;
        }
    }
}
