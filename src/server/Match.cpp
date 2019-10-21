#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"
#include <common/MsgTypes.h>
#include "ThreadClientEventMonitor.h"

#define FRAMES_PER_SECOND 30
#define WELCOME_MATCH_MESSAGE "Welcome to the HELLO game \n"
#define MATCH_JOIN_ERROR "ERROR: Cant JOIN a running match \n"

Match::Match(std::string match_creator, std::string match_name):
    stopped(false),
    updates_race(10000),
    match_name(std::move(match_name)),
    match_creator(std::move(match_creator)),
    clients_monitor(this, this->updates_race)
{}

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
    match_name_to_send.append(this->match_name + " ");
    match_name_to_send.append("Created by: " + this->match_creator);

    if (this->running) {
        match_name_to_send.append("1");
    } else {
        match_name_to_send.append("0");
    }

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
    this->initialize_players();
    this->clients_monitor.start();

    for (auto & player : players) {
        this->updates_players.emplace(player.get_ID(), 10000/*queue len*/);
        this->thread_players.emplace_back(updates_players.at(player.get_ID()), updates_race, player);
        this->create_info_player_updates(player.get_ID());
        thread_players.back().start();
    }

    while (this->running) {
        this->step();
        this->create_update_for_players();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMES_PER_SECOND));
    }
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
    for (auto & car : cars) {
        car.second.update();
    }
    this->racing_track.update();
}

void Match::initialize_players() {
    int32_t ID = 0;
    for (auto & player : players) {
        player.set_ID(ID);
        CarSpecs specs(50, -10, 50, 100, 40, 40);
        this->cars.insert(std::pair<uint8_t, Car&&>(player.get_ID(), std::move(Car(this->racing_track, specs))));
        ID++;
    }
}

void Match::create_update_for_players() {
    for (auto& car : cars){
        auto update = car.second.get_update(car.first);
        this->send_to_all(update);
    }
}

void Match::create_info_player_updates(int32_t player_ID) {
    std::vector<int32_t> car_ID{MSG_CAR_ID, player_ID};
    std::vector<int32_t> track_ID{MSG_TRACK_ID, 1/*esto puede variar despues*/};
    this->updates_players.at(player_ID).push(std::move(UpdateClient(MSG_CAR_ID, std::move(car_ID))));
    this->updates_players.at(player_ID).push(std::move(UpdateClient(MSG_TRACK_ID, std::move(track_ID))));
}

void Match::send_to_all(UpdateClient update) {
    for (auto& queue : updates_players){
        queue.second.push(update);
    }
}
