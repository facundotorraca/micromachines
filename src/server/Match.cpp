#include <mutex>
#include <string>
#include <iostream>
#include "Match.h"
#include "Player.h"

Match::Match(std::string match_creator):
    running(false),
    ready(false),
    stopped(false)
{
    this->match_creator = match_creator;
}

void Match::add_player(Player&& player) {
    /* Controlar si no arranco */
    this->players.push_back(std::move(player));
}

bool Match::is_ready() {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->ready;
}

void Match::start() {
    std::lock_guard<std::mutex> lock(this->mtx);
    this->ready = true;
}

bool Match::is_running() {
    return this->running;
}

void Match::run() {
    this->running = true;
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

