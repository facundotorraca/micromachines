#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include <list>
#include <mutex>
#include <atomic>
#include <string>
#include "Player.h"

class Match {
    std::atomic<bool> stopped;

    std::mutex mtx;
    std::list<Player> players;

    std::string match_name;
    std::string match_creator;

    public:
        explicit Match(std::string match_creator, std::string match_name);

        void send_to_all(std::string message);

        void add_player(Player&& player);

        std::string get_match_name();

        bool ended();

        void stop();
};


#endif //MICROMACHINES_MATCH_H
