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
#include <model/Race.h>
#include "UpdateRace.h"
#include <unordered_map>
#include "ThreadPlayer.h"
#include "UpdateClient.h"
#include <common/Thread.h>
#include "ClientUpdater.h"
#include "model/LapCounter.h"
#include <model/Vehicle/Car.h>
#include <model/RacingTrack.h>
#include <common/ProtectedQueue.h>
#include <model/CountdownTimer.h>
#include "ThreadClientEventMonitor.h"
#include "PluginsManager.h"

class Match : public Thread {
    std::string match_name;
    std::string match_creator;
    std::atomic<bool> closed;

    ThreadClientEventMonitor clients_monitor;

    ClientUpdater client_updater;
    ProtectedQueue<UpdateRace> updates_race;
    std::unordered_map<int32_t, Player> players;
    std::unordered_map<int32_t, ThreadPlayer> thread_players;

    Race race;

    CountdownTimer timer;
    PluginsManager plugins_manager;

    std::mutex mtx;
    std::atomic<bool> waiting_restart;

    private:
        void step();

        void close();

        void run() override;

        void update_players();

        void initialize_players();

        bool all_players_finished();

        void select_new_creator();

        void remove_disconnected_players();

        void wait_match_creator_decision();

    public:
        explicit Match(std::string match_creator, std::string match_name);

        void set_restart_option(UpdateRace update);

        bool has_username(std::string& username);

        void apply_update(UpdateRace update);

        std::string get_match_name_to_send();

        void change_map(std::string new_map);

        void add_player(Player&& player);

        std::string get_match_name();

        void send_cancel_match_flag();

        void restart_match();

        bool is_closed();

        void kill();
};


#endif //MICROMACHINES_MATCH_H
