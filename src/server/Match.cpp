#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"
#include "MapLoader.h"
#include <common/MsgTypes.h>
#include <common/SocketError.h>
#include "ThreadClientEventMonitor.h"

#define FRAMES_PER_SECOND 60

#define ERROR_MATCH_JOIN_FLAG 1
#define SUCCESS_MATCH_JOIN_FLAG 0

#define OPEN_MATCH_FLAG "0"
#define CLOSE_MATCH_FLAG "1"

#define START_MATCH_FLAG 0

#define MAP_PATH "maps/"

Match::Match(std::string match_creator, std::string match_name):
    stopped(false),
    map_loader(MAP_PATH),
    game_rules(5),
    updates_race(10000),
    match_name(std::move(match_name)),
    match_creator(std::move(match_creator)),
    clients_monitor(this, this->updates_race)
{}

void Match::add_player(Player&& player) {
    try {
        if (this->running) {
            player.send((uint8_t)ERROR_MATCH_JOIN_FLAG);
        } else {
            player.send((uint8_t)SUCCESS_MATCH_JOIN_FLAG);
            player.set_ID((int32_t)players.size());
            this->players.emplace(players.size(),std::move(player));
        }
    } catch (const SocketError& exception) {
        std::cerr << "Player disconnected during match creation\n";
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
    for (auto &player : this->players) {
        player.second.kill();
    }
    this->remove_disconnected_players();
}

void Match::run() {
    this->initialize_map();
    this->initialize_players();
    this->initialize_thread_players();
    this->create_general_update_for_players();

    this->clients_monitor.start();

    //contador
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    while (this->running) {
        this->step();
        this->create_general_update_for_players(); //Update related with view
        this->create_specific_update_for_players(); //Updates related with info
        this->remove_disconnected_players();

        if (this->players.empty()) {
            this->close();
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMES_PER_SECOND));
    }
    //wait partida
}

void Match::close() {
    this->updates_race.close();
    this->clients_monitor.join();
    this->running = false;
    /*Used by the MatchTable, a non started
    match is also not running, but not dead*/
    this->stopped = true;
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
        CarSpecs specs{100, 120, -20, 130, 150, 8.5, 7.5};
        this->cars.emplace(std::piecewise_construct,
                           std::forward_as_tuple(player.first),
                           std::forward_as_tuple(racing_track, specs));

        try {
            player.second.send((uint8_t)START_MATCH_FLAG);
            player.second.send_track(this->racing_track);
        } catch (const SocketError& exception) {
            std::cerr << "Player disconnected\n";
            this->players.erase(player.first);
        }
    }
    this->map_loader.set_cars_spawn_point(this->cars);
}

void Match::create_general_update_for_players() {
    for (auto& car : cars) {
        auto update = car.second.get_update(car.first);
        this->send_to_all(update);
    }
}

void Match::create_info_player_updates(int32_t player_ID) {
    std::vector<int32_t> car_ID_update_info{MSG_CAR_ID, player_ID};
    this->updates_players.at(player_ID).push(std::move(UpdateClient(std::move(car_ID_update_info))));
}

void Match::send_to_all(UpdateClient update) {
    for (auto& queue : updates_players){
        queue.second.push(update);
    }
}

void Match::initialize_map() {
    /* Aca podriamos leer el archivo de configs para los nombres*/
    this->map_loader.load_map(this->racing_track, "track_01.json", "tiles.json");
}

void Match::remove_disconnected_players() {
    for (auto th_player = this->thread_players.begin(); th_player != this->thread_players.end();) {
        if ((*th_player).second.dead()) {
            (*th_player).second.join();
            this->cars.erase((*th_player).first);
            this->players.erase((*th_player).first);
            this->updates_players.erase((*th_player).first);
            th_player =  this->thread_players.erase(th_player);
        } else {
            th_player++;
        }
    }
}

void Match::initialize_thread_players() {
    for (auto& player : players) {
        int32_t id = player.first;
        this->updates_players.emplace(id, 10000/*queue len*/);
        this->thread_players.emplace(std::piecewise_construct,
                                     std::forward_as_tuple(id),
                                     std::forward_as_tuple(updates_players.at(id),updates_race, player.second));
        this->create_info_player_updates(id); /* Send own car ID and race track ID*/
        this->thread_players.at(id).start();
    }
}

void Match::create_specific_update_for_players() {
    for (auto& car : cars) {
        if (car.second.lap_was_completed()) {
            game_rules.add_lap(car.first);
            game_rules.get_update(car.first);
        }
        if (car.second.lap_was_restarted()) {
            game_rules.take_lap(car.first);
            game_rules.get_update(car.first);
        }
    }
}


