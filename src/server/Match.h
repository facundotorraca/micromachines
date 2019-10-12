#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include <list>
#include <mutex>
#include <atomic>
#include <string>
#include "Player.h"

class Match {
    std::atomic<bool> ready;
    std::atomic<bool> stopped;
    std::atomic<bool> running;

    std::mutex mtx;
    std::list<Player> players;
    std::string match_creator;

    public:
        explicit Match(std::string match_creator);

        void send_to_all(std::string message);

        void add_player(Player&& player);

        bool is_running();

        bool is_ready();

        void start();

        bool ended();

        void run();

        void stop();
};


#endif //MICROMACHINES_MATCH_H
