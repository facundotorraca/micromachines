#ifndef MICROMACHINES_THREADMATCHOPTIONS_H
#define MICROMACHINES_THREADMATCHOPTIONS_H

#include "Thread.h"
#include "Match.h"
#include <atomic>
#include "Player.h"
#include "ProtectedQueueMatch.h"

class ThreadMatchOptions : public Thread {
    ProtectedQueueMatch& not_ready_matches;

    Match* match;
    Player creator;

    std::atomic<bool> dead{};

    private:
        void run() override;

    public:
        ThreadMatchOptions(Player &&player, Match* match, ProtectedQueueMatch& not_ready_matches);

        bool options_set();

};


#endif //MICROMACHINES_THREADMATCHOPTIONS_H
