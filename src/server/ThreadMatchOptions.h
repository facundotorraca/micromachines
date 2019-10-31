#ifndef MICROMACHINES_THREADMATCHOPTIONS_H
#define MICROMACHINES_THREADMATCHOPTIONS_H

#include <thread>
#include <memory>
#include <atomic>
#include "server/Match.h"
#include "common/Thread.h"
#include "server/Player.h"
#include "common/ProtectedQueue.h"

class ThreadMatchOptions {
    std::shared_ptr<Match> match;
    std::thread thread;
    Player player;

    std::atomic<bool> dead;

    private:
        void run_match_options(ProtectedQueue<std::shared_ptr<Match>>* not_ready_matches);

        void run_player_options();

    public:
        ThreadMatchOptions(Player &&player, std::shared_ptr<Match>&& match);

        void start_match_options(ProtectedQueue<std::shared_ptr<Match>>* not_ready_matches);

        void start_player_options();

        bool options_set();

        void stop();

        void join();
};



#endif //MICROMACHINES_THREADMATCHOPTIONS_H
