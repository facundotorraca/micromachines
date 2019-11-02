#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"
#include "MapLoader.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/SocketError.h>
#include <model/CountdownTimer.h>
#include "ThreadClientEventMonitor.h"
#include <server/FramesSyncronizer.h>

#define MAP_PATH "maps/"

#define ERROR_MATCH_JOIN_FLAG 1

#define OPEN_MATCH_FLAG "0"
#define CLOSE_MATCH_FLAG "1"

#define SUCCESS_MATCH_JOIN_FLAG 0

#define START_MATCH_FLAG 0

#define TIME_START 3

Match::Match(std::string match_creator, std::string match_name):
        closed(false),
        lap_counter(5),
        updates_race(10000),
        match_name(std::move(match_name)),
        match_creator(std::move(match_creator)),
        clients_monitor(this, this->updates_race)
{}

void Match::add_player(Player&& player) {
    try {
        if (this->running) {
            std::cout << "ENTRE\n";
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

void Match::kill() {
    for (auto &player : this->players) {
        player.second.kill();
    }
    this->remove_disconnected_players();
}

void Match::close() {
    this->updates_race.close();
    this->clients_monitor.join();
    this->running = false;
    this->closed = true;
    /*Used by the MatchTable, a non started
    match is also not running, but not dead*/
}

bool Match::is_closed() {
    return this->closed;
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

void Match::update_players() {
    for (auto& car : cars) {
        auto general_update = car.second.get_update(car.first);
        this->send_to_all(general_update);

        if (this->lap_counter.car_complete_laps(car.first)) {
            this->thread_players.at(car.first).set_player_on_hold();
        }

        car.second.modify_laps(this->lap_counter, car.first);
        auto personalized_update = this->lap_counter.get_update(car.first);
        this->updates_players.at(car.first).push(personalized_update);
    }
}

void Match::send_to_all(UpdateClient update) {
    for (auto& queue : updates_players){
        queue.second.push(update);
    }
}

void Match::apply_update(UpdateRace update) {
    std::unique_lock<std::mutex> lock(mtx);
    update.update_cars(this->cars);
}

void Match::run() {
    CountdownTimer timer(TIME_START, this->thread_players, this->updates_players);
    this->initialize_players();
    this->clients_monitor.start();
    timer.start();

    while (this->running) {
        this->step();
        this->update_players();
        this->remove_disconnected_players();

        if (this->players.empty()) {
            this->close();
            timer.join();
            return;
        }
    }
    timer.join();
}

void Match::step() {
    FramesSynchronizer::sync_FPS(FRAMES_PER_SECOND);
    std::unique_lock<std::mutex> lock(mtx);
    for (auto &car : cars) {
        car.second.update();
    }
    this->racing_track.update();
}

void Match::initialize_players() {
    MapLoader map_loader(MAP_PATH);
    map_loader.load_map(this->racing_track, "track_01.json", "tiles.json");

    for (auto& player : players) {
        int32_t ID = player.first;

        CarSpecs specs{100, 120, -20, 130, 150, 8.5, 7.5};
        this->cars.emplace(std::piecewise_construct,
                           std::forward_as_tuple(player.first),
                           std::forward_as_tuple(racing_track, specs));


        this->updates_players.emplace(ID, 10000/*queue len*/);
        this->thread_players.emplace(std::piecewise_construct,
                                     std::forward_as_tuple(ID),
                                     std::forward_as_tuple(updates_players.at(ID),
                                                           updates_race, player.second));



        try {
            this->players.at(ID).send((uint8_t)START_MATCH_FLAG);
            this->thread_players.at(ID).start();
            this->create_initial_player_info(ID);
        } catch (const SocketError& exception) {
            std::cerr << "Player disconnected\n";
            this->players.erase(player.first);
            //aca no va un break?
        }

    }
    map_loader.set_cars_spawn_point(this->cars);
}

void Match::create_initial_player_info(int32_t player_ID) {
    int32_t total_laps = this->lap_counter.get_total_laps();
    this->updates_players.at(player_ID).push(std::move(UpdateClient({MSG_BEGIN_LOADING})));
    this->racing_track.send(this->updates_players.at(player_ID));
    this->updates_players.at(player_ID).push(std::move(UpdateClient({MSG_TOTAL_LAPS, total_laps})));
    this->updates_players.at(player_ID).push(std::move(UpdateClient({MSG_CAR_ID, player_ID})));
    this->updates_players.at(player_ID).push(std::move(UpdateClient({MSG_FINISH_LOADING})));
}
