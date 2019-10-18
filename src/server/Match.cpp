#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"

#define WELCOME_MATCH_MESSAGE "Welcome to the HELLO game \n"
#define MATCH_JOIN_ERROR "ERROR: Cant JOIN a running match \n"

Match::Match(std::string match_creator, std::string match_name):
    stopped(false),
    running(false)
{
    this->match_name = std::move(match_name);
    this->match_creator = std::move(match_creator);
}

void Match::add_player(Player&& player) {
    if (this->running) {
        /*averiguar sobre la excepcion aca*/
        std::string match_error(MATCH_JOIN_ERROR);
        player.send(match_error);
    } else {
        std::string welcome_message(WELCOME_MATCH_MESSAGE);
        player.send(welcome_message);
        this->players.push_back(std::move(player));
    }
}

void Match::send_to_all(std::vector<uint8_t>& message) {
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

bool Match::has_username(std::string& username) {
    for (auto& player : this->players) {
        if (player.is_called(username)) {
            return true;
        }
    }
    /* Match creator is added at the end*/
    return this->match_creator == username;
}
