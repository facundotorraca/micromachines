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
#include "model/LapCounter.h"

class Match : public Thread {
    std::string match_name;
    std::string match_creator;
    std::atomic<bool> closed;

    ThreadClientEventMonitor clients_monitor;

    ProtectedQueue<UpdateRace> updates_race;

    std::unordered_map<int32_t, bool> player_running;

    std::unordered_map<int32_t, Car> cars;
    std::unordered_map<int32_t, Player> players;
    std::unordered_map<int32_t, ThreadPlayer> thread_players;
    std::unordered_map<int32_t, ProtectedQueue<UpdateClient>> updates_players;

    RacingTrack racing_track;
    LapCounter lap_counter;

    std::mutex mtx;

    private:
        void step();

        void close();

        void run() override;

        void update_players();

        void initialize_players();

        void remove_disconnected_players();

        void send_to_all(UpdateClient update);

        void create_initial_player_info(int32_t player_ID);

    public:
        explicit Match(std::string match_creator, std::string match_name);

        bool has_username(std::string& username);

        void apply_update(UpdateRace update);

        std::string get_match_name_to_send();

        void add_player(Player&& player);

        bool is_closed();

        void kill();
};


#endif //MICROMACHINES_MATCH_H
