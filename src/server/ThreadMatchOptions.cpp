#include <iostream>
#include "ThreadMatchOptions.h"
#include "Player.h"

#define START_MATCH 1

ThreadMatchOptions::ThreadMatchOptions(Player &&player, Match* match):
    creator(std::move(player)),
    dead(false)
{
    this->match = match;
}

void ThreadMatchOptions::run() {
    uint8_t option = 0;

    while (option != START_MATCH) {
        option = this->creator.receive_option();
        /*
         * MATCH APLICATE OPTION
         */
    }
    /*Put the creator on the match*/
    this->match->add_player(std::move(creator));
    this->match->start();

    this->dead = true;
}

bool ThreadMatchOptions::options_setted() {
    return this->dead;
}
