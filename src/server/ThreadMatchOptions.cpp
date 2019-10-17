#include <iostream>
#include <utility>
#include "server/Player.h"
#include "ThreadMatchOptions.h"
#include <common/SocketError.h>
#include "common/ProtectedQueue.h"

#define START_MATCH 1

ThreadMatchOptions::ThreadMatchOptions(Player&& player, std::shared_ptr<Match>&& match, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches):
    not_ready_matches(not_ready_matches),
    creator(std::move(player)),
    match(std::move(match)),
    dead(false)
{}

void ThreadMatchOptions::run() {
    try {
        uint8_t option = 0;

        while (option != START_MATCH) {
            option = this->creator.receive_option();
            /*MATCH APPLY OPTION*/
        }
        /*Put the creator on the match*/
        this->match->add_player(std::move(creator));
        this->not_ready_matches.push(this->match);
        this->dead = true;
    } catch (const SocketError& exception) {
        this->dead = true;
    }
}


bool ThreadMatchOptions::options_set() {
    return this->dead;
}

void ThreadMatchOptions::stop() {
    this->creator.kill();
    this->dead = true;
}
