#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include <list>
#include <mutex>
#include <atomic>
#include <string>
#include "Player.h"

class Match {
    std::atomic<bool> ready;
    std::atomic<bool> stoped;
    std::atomic<bool> running;

    std::mutex mtx;
    std::list<Player> players;
    std::string match_creator;

    public:
        explicit Match(std::string match_creator);

        void add_player(Player&& player);

        bool is_running();

        bool is_ready();

        void start();

        void run();

        void send_to_all(std::string message);


    void stop();

    bool ended();
};


#endif //MICROMACHINES_MATCH_H
