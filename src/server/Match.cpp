#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"
#include <common/MsgTypes.h>
#include <iostream>
#include "ThreadClientEventMonitor.h"

#define FRAMES_PER_SECOND 30

#define ERROR_MATCH_JOIN_FLAG 1
#define SUCCESS_MATCH_JOIN_FLAG 0

#define OPEN_MATCH_FLAG "0"
#define CLOSE_MATCH_FLAG "1"

#define START_MATCH_FLAG 0

Match::Match(std::string match_creator, std::string match_name):
    stopped(false),
    updates_race(10000),
    match_name(std::move(match_name)),
    match_creator(std::move(match_creator)),
    clients_monitor(this, this->updates_race)
{}

void Match::add_player(Player&& player) {
    uint8_t flag;
    if (this->running) {
        flag = ERROR_MATCH_JOIN_FLAG;
        player.send(flag);
    } else {
        flag = SUCCESS_MATCH_JOIN_FLAG;
        player.send(flag);
        player.set_ID((int32_t)players.size());
        this->players.emplace(players.size(),std::move(player));
    }
}

std::string Match::get_match_name_to_send() {
    std::string match_name_to_send;
    match_name_to_send.append(this->match_name + " ");
    match_name_to_send.append("Created by: " + this->match_creator);

    if (this->running) {
        match_name_to_send.append(CLOSE_MATCH_FLAG);
    } else {
        match_name_to_send.append(OPEN_MATCH_FLAG);
    }

    match_name_to_send.append("\n");

    return match_name_to_send;
}

bool Match::has_username(std::string& username) {
    for (auto& player : this->players) {
        if (player.second.is_called(username)) {
            return true;
        }
    }
    /* Match creator is added at the end*/
    return this->match_creator == username;
}

bool Match::was_stopped() {
    return this->stopped;
}

void Match::stop() {
    this->running = false;
    this->stopped = true;
    this->updates_race.close();
}

std::string Match::get_match_name() {
    return this->match_name;
}

std::string Match::get_match_creator() {
    return this->match_creator;
}

void Match::run() {
    this->initialize_players();
    this->clients_monitor.start();

    for (auto& player : players) {
        int32_t id = player.first;
        this->updates_players.emplace(id, 10000/*queue len*/);
        this->thread_players.emplace(std::piecewise_construct,
                                     std::forward_as_tuple(id),
                                     std::forward_as_tuple(updates_players.at(id), updates_race, player.second));
        this->create_info_player_updates(id); /* Send own car ID and race track ID*/
        this->thread_players.at(id).start();
    }

    while (this->running) {
        this->step();
        this->create_update_for_players();
        for (auto &th_player : thread_players) {
            if (th_player.second.dead()) {
                th_player.second.join();
                this->cars.erase(th_player.first);
                this->players.erase(th_player.first);
                this->updates_players.erase(th_player.first);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMES_PER_SECOND));
    }

    //this->updates_race.close();
    this->clients_monitor.join();
}

bool Match::is_runnig() {
    return this->running;
}

void Match::apply_update(UpdateRace update) {
    std::unique_lock<std::mutex> lock(mtx);
    update.update_cars(this->cars);
}

void Match::step() {
    std::unique_lock<std::mutex> lock(mtx);
    for (auto &car : cars) {
        car.second.update();
    }
    this->racing_track.update();
}

void Match::initialize_players() {
    for (auto& player : players) {
        CarSpecs specs(50, -10, 50, 100, 40, 40);
        this->cars.emplace(std::piecewise_construct,
                           std::forward_as_tuple(player.first),
                           std::forward_as_tuple(racing_track, specs));

        uint8_t flag_match_start = START_MATCH_FLAG;
        player.second.send(flag_match_start);
    }
}

void Match::create_update_for_players() {
    for (auto& car : cars){
        auto update = car.second.get_update(car.first);
        this->send_to_all(update);
    }
}

void Match::create_info_player_updates(int32_t player_ID) {
    std::vector<int32_t> car_ID_update_info{MSG_CAR_ID, player_ID};
    std::vector<int32_t> track_ID_update_info{MSG_TRACK_ID, 1/*esto puede variar despues*/};

    this->updates_players.at(player_ID).push(std::move(UpdateClient(std::move(car_ID_update_info))));
    this->updates_players.at(player_ID).push(std::move(UpdateClient(std::move(track_ID_update_info))));
}

void Match::send_to_all(UpdateClient update) {
    for (auto& queue : updates_players){
        queue.second.push(update);
    }
}
