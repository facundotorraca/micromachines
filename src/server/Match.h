#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include <map>
#include <list>
#include <mutex>
#include <vector>
#include <atomic>
#include <string>
#include <thread>
#include "Player.h"
#include "MapLoader.h"
#include "UpdateRace.h"
#include <unordered_map>
#include "ThreadPlayer.h"
#include "UpdateClient.h"
#include <common/Thread.h>
#include <model/Vehicle/Car.h>
#include <model/RacingTrack.h>
#include <common/ProtectedQueue.h>
#include "ThreadClientEventMonitor.h"

class Match : public Thread {
    std::string match_name;
    std::string match_creator;
    std::atomic<bool> stopped;

    ThreadClientEventMonitor clients_monitor;

    ProtectedQueue<UpdateRace> updates_race;

    std::unordered_map<int32_t, Player> players;
    std::unordered_map<int32_t, ThreadPlayer> thread_players;
    std::unordered_map<int32_t, ProtectedQueue<UpdateClient>> updates_players;
    std::unordered_map<int32_t, Car> cars;

    RacingTrack racing_track;

    MapLoader map_loader;

    std::mutex mtx;

    private:
        void step();

        void run() override;

        void initialize_map();

        void initialize_players();

        void initialize_thread_players();

        void create_update_for_players();

        void remove_disconnected_players();

        void send_to_all(UpdateClient update);

        void create_info_player_updates(int32_t player_ID);

    public:
        explicit Match(std::string match_creator, std::string match_name);

        bool has_username(std::string& username);

        void apply_update(UpdateRace update);

        std::string get_match_name_to_send();

        void add_player(Player&& player);

        bool was_stopped();

        void stop();

};


#endif //MICROMACHINES_MATCH_H
