#include <string>
#include <utility>
#include "Match.h"
#include "Player.h"
#include <common/Sizes.h>
#include <model/DTO_Info.h>
#include <common/SocketError.h>
#include <model/CountdownTimer.h>
#include "ThreadClientEventMonitor.h"
#include <server/FramesSyncronizer.h>

#define MAP_PATH "maps/"
#define MAP_NAME "track_01.json"

#define PLUGINGS_PATH "plugings/"

#define ERROR_MATCH_JOIN_FLAG 1

#define OPEN_MATCH_FLAG "0"
#define CLOSE_MATCH_FLAG "1"

#define SUCCESS_MATCH_JOIN_FLAG 0

#define START_MATCH_FLAG 0
#define TIME_START 3

#define UPDATE_QUEUE_MAX_SIZE 1000

Match::Match(std::string match_creator, std::string match_name):
    closed(false),
    updates_race(10000),
    match_name(std::move(match_name)),
    race(3, MAP_PATH, MAP_NAME),
    match_creator(std::move(match_creator)),
    clients_monitor(this, this->updates_race),
    plugings_manager(race, PLUGINGS_PATH)
{
    std::cout << "INICIALIZO MATH" << std::endl;
    this->plugings_manager.load_plugings();
}

void Match::add_player(Player&& player) {
    try {
        if (this->running)
            player.send((uint8_t)ERROR_MATCH_JOIN_FLAG);
        else {
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
    match_name_to_send.append(this->running ? CLOSE_MATCH_FLAG : OPEN_MATCH_FLAG);
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
    /*Close is used by the MatchTable,
    a non started  match is also not running,
    but not dead*/
    this->updates_race.close();
    this->clients_monitor.join();
    this->running = false;
    this->closed = true;
}

bool Match::is_closed() {
    return this->closed;
}

void Match::initialize_players() {
    for (auto& player : players) {
        int32_t ID = player.first;

        CarSpecs specs{100, 120, -20, 130, 150, 8.5, 7.5};
        this->race.add_car_with_specs(player.first, specs);

        this->client_updater.create_update_queue(ID, UPDATE_QUEUE_MAX_SIZE);
        this->thread_players.emplace(std::piecewise_construct, std::forward_as_tuple(ID),
                                                               std::forward_as_tuple(this->client_updater,
                                                                                      updates_race, player.second));

        try {
            this->players.at(ID).send((uint8_t)START_MATCH_FLAG);
            this->thread_players.at(ID).start();
            this->race.send_info_to_player(ID, this->client_updater);
        } catch (const SocketError& exception) {
            std::cerr << "Player disconnected\n";
            this->players.erase(player.first);
            this->thread_players.at(ID).join();
            this->thread_players.erase(ID);
            this->race.player_left_game(ID);
        }
    }
}

void Match::remove_disconnected_players() {
    for (auto th_player = this->thread_players.begin(); th_player != this->thread_players.end();) {
        if ((*th_player).second.dead()) {
            (*th_player).second.join();
            this->race.player_left_game((*th_player).first);
            this->players.erase((*th_player).first);
            this->client_updater.remove_queue((*th_player).first);
            th_player =  this->thread_players.erase(th_player);
        } else {
            th_player++;
        }
    }
}

void Match::apply_update(UpdateRace update) {
    std::unique_lock<std::mutex> lock(mtx);
    this->race.update_cars(update);
    update.update_player_view(this->players);
}

void Match::step() {
    FramesSynchronizer::sync_FPS(FRAMES_PER_SECOND);
    std::unique_lock<std::mutex> lock(mtx);
    this->race.update();
    this->plugings_manager.execute();
}

void Match::update_players() {
    for (auto& player : this->players) {
        int32_t ID = player.first;

        this->race.send_general_updates_of_player(ID, this->client_updater);

        if (this->players.at(ID).is_playing() && this->race.car_complete_laps(ID)) {
            this->players.at(ID).set_finished(this->client_updater);

        }

        if (!this->players.at(ID).is_playing())
            this->players.at(ID).update_view(players.size(), client_updater);
    }
}

void Match::run() {
    CountdownTimer timer(TIME_START,this->race, this->client_updater);
    this->initialize_players();

    DTO_Info dto;
    this->race.get_dto_data(dto);

    this->clients_monitor.start();
    timer.start();
    while (this->running) {
        this->step();
        this->update_players();
        this->remove_disconnected_players();

        if (this->players.empty()) {
            timer.join();
            this->close();
            return;
        }
    }

    timer.join();
}
