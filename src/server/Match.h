#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include <list>
#include <mutex>
#include <atomic>
#include <string>
#include "Player.h"

class Match {
    std::atomic<bool> stopped;
    std::atomic<bool> running;

    std::list<Player> players;

    std::string match_name;
    std::string match_creator;

    public:
        explicit Match(std::string match_creator, std::string match_name);

        std::string get_match_name_to_send(int match_index);

        bool has_username(std::string& username);

        void send_to_all(std::string& message);

        void add_player(Player&& player);

        std::string get_match_creator();

        std::string get_match_name();

        bool ended();

        void stop();

        void run();
};


#endif //MICROMACHINES_MATCH_H
