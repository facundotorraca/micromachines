#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"

Match::Match(std::string match_creator, std::string match_name):
    stopped(false),
    running(false)
{
    this->match_name = std::move(match_name);
    this->match_creator = std::move(match_creator);
}

void Match::add_player(Player&& player) {
    /* Controlar si no arranco */
    this->players.push_back(std::move(player));
}

void Match::send_to_all(std::string& message) {
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

std::string Match::get_match_creator() {
    return this->match_creator;
}

std::string Match::get_match_name_to_send(int match_index) {
    std::string match_name_to_send;
    match_name_to_send.append("Match (" +  std::to_string(match_index) + ")");
    match_name_to_send.append(" " + this->match_name + " ");
    match_name_to_send.append("Created by: " + this->match_creator);
    if (this->running) match_name_to_send.append(" c||");
    match_name_to_send.append("\n");
    return match_name_to_send;
}

void Match::run() {
    this->running = true;
}
