#include "Player.h"
#include <iostream>
#include "ProtectedQueue.h"
#include "ThreadMatchOptions.h"

#define START_MATCH 1

ThreadMatchOptions::ThreadMatchOptions(Player&& player, Match* match, ProtectedQueue<Match*>& not_ready_matches):
    not_ready_matches(not_ready_matches),
    creator(std::move(player)),
    dead(false)
{
    this->match = match;
}

void ThreadMatchOptions::run() {
    uint8_t option = 0;

    while (option != START_MATCH) {
        option = this->creator.receive_option();
        /*MATCH APPLY OPTION*/
    }
    /*Put the creator on the match*/
    this->match->add_player(std::move(creator));
    this->not_ready_matches.push(this->match);
    this->dead = true;
}

bool ThreadMatchOptions::options_set() {
    return this->dead;
}
