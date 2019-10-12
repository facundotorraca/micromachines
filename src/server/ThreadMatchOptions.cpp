#include <iostream>
#include "ThreadMatchOptions.h"
#include "Player.h"

#define START_MATCH 1

ThreadMatchOptions::ThreadMatchOptions(Player &&player, Match* match, ProtectedQueueMatch& not_ready_matches):
    creator(std::move(player)),
    not_ready_matches(not_ready_matches),
    dead(false)
{
    this->match = match;
}

void ThreadMatchOptions::run() {
    uint8_t option = 0;

    while (option != START_MATCH) {
        option = this->creator.receive_option();
        /*MATCH APLICATE OPTION*/
    }
    /*Put the creator on the match*/
    this->match->add_player(std::move(creator));
    this->match->start();
    this->not_ready_matches.push(this->match);
    this->dead = true;
}

bool ThreadMatchOptions::options_set() {
    return this->dead;
}
