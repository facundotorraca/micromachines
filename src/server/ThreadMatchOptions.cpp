#include <iostream>
#include <utility>
#include "server/Player.h"
#include "ThreadMatchOptions.h"
#include <common/SocketError.h>
#include "common/ProtectedQueue.h"

#define START_MATCH 1

ThreadMatchOptions::ThreadMatchOptions(Player&& player, std::shared_ptr<Match>&& match):
    player(std::move(player)),
    match(std::move(match)),
    dead(false)
{}

void ThreadMatchOptions::start_match_options(ProtectedQueue<std::shared_ptr<Match>>* not_ready_matches) {
    this->thread = std::thread(&ThreadMatchOptions::run_match_options, this, not_ready_matches);
}

void ThreadMatchOptions::start_player_options() {
    this->thread = std::thread(&ThreadMatchOptions::run_player_options, this);
}

bool ThreadMatchOptions::options_set() {
    return this->dead;
}

void ThreadMatchOptions::stop() {
    this->player.kill();
    this->dead = true;
}

void ThreadMatchOptions::run_match_options(ProtectedQueue<std::shared_ptr<Match>>* not_ready_matches) {
    try {
        uint8_t option = 0;

        while (option != START_MATCH) {
            option = this->player.receive_option();
            /*MATCH APPLY OPTION*/
        }
        /*Put the creator on the match*/
        this->match->add_player(std::move(player));
        not_ready_matches->push(this->match);
        this->dead = true;
    } catch (const SocketError& exception) {
        this->dead = true;
    }
}

void ThreadMatchOptions::run_player_options() {
    try {
        uint8_t option = 0;

        option = this->player.receive_option();
        this->player.set_car_model(option);

        /*FALTAS MAS OPCIONES DE JUGADOR*/

        this->match->add_player(std::move(player));
        this->dead = true;
    } catch (const SocketError& exception) {
        this->dead = true;
    }
}

void ThreadMatchOptions::join() {
    this->thread.join();
}
