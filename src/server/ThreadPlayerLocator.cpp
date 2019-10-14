#include <list>
#include <memory>
#include "Match.h"
#include "Player.h"
#include <iostream>
#include "MatchTable.h"
#include "ProtectedQueue.h"
#include "ThreadPlayerLocator.h"

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
    /* creo que esta incompleto*/
    this->server_running = false;
}

void ThreadPlayerLocator::run() {
    while (this->server_running) {
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
    }
}
