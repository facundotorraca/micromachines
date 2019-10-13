#include <mutex>
#include <string>
#include "Match.h"
#include "Player.h"

Match::Match(std::string match_creator, std::string match_name):
    stopped(false)
{
    this->match_name = match_name;
    this->match_creator = match_creator;
}

void Match::add_player(Player&& player) {
    /* Controlar si no arranco */
    this->players.push_back(std::move(player));
}

void Match::send_to_all(std::string message) {
    for (auto& player : this->players) {
        player.send(message);
    }
}

bool Match::ended() {
    return this->stopped;
}

void Match::stop() {
    this->stopped = true;
}

std::string Match::get_match_name() {
    return this->match_name;
}

