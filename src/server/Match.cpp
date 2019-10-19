#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"
#include "ThreadClientEventMonitor.h"
#include <common/EntityType.h>
#include <common/MsgTypes.h>

#define FRAMES_PER_SECOND 30
#define WELCOME_MATCH_MESSAGE "Welcome to the HELLO game \n"
#define MATCH_JOIN_ERROR "ERROR: Cant JOIN a running match \n"

Match::Match(std::string match_creator, std::string match_name):
    stopped(false),
    updates_race(10000)
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

void Match::send_to_all(std::vector<int32_t>& message) {
    for (auto& player : this->players) {
        player.send(message);
    }
}

bool Match::was_stopped() {
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

bool Match::has_username(std::string& username) {
    for (auto& player : this->players) {
        if (player.is_called(username)) {
            return true;
        }
    }
    /* Match creator is added at the end*/
    return this->match_creator == username;
}

void Match::run() {
    for (size_t i = 0; i < this->players.size(); i++) {
        players[i].set_ID(i);
    }

    for (auto & player : players) {
        CarSpecs specs(250, -40, 300, 500, 40, 40);
        this->cars.emplace(player.get_ID(), this->racing_track, specs);
    }

    ThreadClientEventMonitor client_monitor(this, updates_race);
    client_monitor.start();

    for (auto & player : players) {
        this->updates_for_clients.emplace(player.get_ID(), 100);
        this->thread_players.emplace_back(updates_race,
                updates_for_clients.at(player.get_ID()), player);
        thread_players.back().start();
    }

    while (running) {
        this->step();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMES_PER_SECOND));
    }


    /*
    bool a = true;
    int32_t i = 0;

    std::vector<int32_t> hola{MSG_CAR_ID, 1};
    std::vector<int32_t> track{MSG_MAP, 1};
    this->send_to_all(hola);
    this->send_to_all(track);
    while (this->running)  {
        i+=3;
        std::vector<int32_t> chau{MSG_UPDATE_ENTITY, 2, TYPE_CAR, 30, 10, 30};
        std::vector<int32_t> hola2{MSG_UPDATE_ENTITY, 1, TYPE_CAR, i, 100, 0};
        this->send_to_all(hola2);
        this->send_to_all(chau);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    */
}

bool Match::is_runnig() {
    return this->running;
}

void Match::apply_update(UpdateRace update) {
    update.update_cars(this->cars);
}

void Match::step() {
    for (auto& car : cars){
        car.second.update();
    }
    racing_track.update();
}
