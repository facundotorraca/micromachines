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
#include <model/Car.h>
#include "UpdateRace.h"
#include "ThreadPlayer.h"
#include "UpdateClient.h"
#include <common/Thread.h>
#include <model/RacingTrack.h>
#include <common/ProtectedQueue.h>
#include <unordered_map>
#include "ThreadClientEventMonitor.h"

class Match : public Thread {
    std::string match_name;
    std::string match_creator;
    std::atomic<bool> stopped;

    ThreadClientEventMonitor clients_monitor;

    ProtectedQueue<UpdateRace> updates_race;

    std::unordered_map<uint8_t, Player> players;
    std::unordered_map<uint8_t, ThreadPlayer> thread_players;
    std::unordered_map<uint8_t, ProtectedQueue<UpdateClient>> updates_players;
    std::unordered_map<uint8_t, Car> cars;

    RacingTrack racing_track;

    std::mutex mtx;
    private:
        void run() override;

        void initialize_players();

        void create_update_for_players();

        void create_info_player_updates(int32_t player_ID);

        void send_to_all(UpdateClient update);

    public:
        explicit Match(std::string match_creator, std::string match_name);

        std::string get_match_name_to_send(int match_index);

        bool has_username(std::string& username);

        void apply_update(UpdateRace update);

        void add_player(Player&& player);

        std::string get_match_creator();

        std::string get_match_name();

        bool was_stopped();

        bool is_runnig();

        void stop();

        void step();

};


#endif //MICROMACHINES_MATCH_H
