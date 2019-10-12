#include <list>
#include "Match.h"
#include "Player.h"
#include <iostream>
#include "ProtectedMap.h"
#include "ProtectedQueue.h"
#include "ThreadPlayerLocator.h"

ThreadPlayerLocator::ThreadPlayerLocator(ProtectedQueue& incoming_players,
                                         ProtectedMap &matches):
        matches(matches),
        incoming_players(incoming_players),
        server_running(true)
{}

void ThreadPlayerLocator::remove_running_matches() {
    for (auto options_setter = this->options_setters.begin(); options_setter != this->options_setters.end();) {
        if ((*options_setter)->options_setted()) {
            (*options_setter)->join();
            delete (*options_setter);
            options_setter = options_setters.erase(options_setter);
        } else {
            options_setter++;
        }
    }
}

void ThreadPlayerLocator::run() {
    while (this->server_running) {
        Player new_player = this->incoming_players.pop();
        std::string match_name = new_player.get_match_name();

        if (new_player.is_on_join_mode()) {
            Match* match = this->matches.get(match_name);
            match->add_player(std::move(new_player));
        } else {
            auto* new_match = new Match(new_player.get_username());
            this->matches.add(match_name, new_match);

            auto* options_setter = new ThreadMatchOptions(std::move(new_player), new_match);
            this->options_setters.push_back(options_setter);
            options_setter->start();
        }

        this->remove_running_matches();
    }
}

void ThreadPlayerLocator::stop() {
    /*No creo que este bien del todoo!*/
    this->server_running = false;
}
