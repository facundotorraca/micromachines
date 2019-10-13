#ifndef MICROMACHINES_THREADMATCHOPTIONS_H
#define MICROMACHINES_THREADMATCHOPTIONS_H

#include "Thread.h"
#include "Match.h"
#include <atomic>
#include "Player.h"
#include "ProtectedQueue.h"

class ThreadMatchOptions : public Thread {
    ProtectedQueue<Match*>& not_ready_matches;

    Match* match;
    Player creator;

    std::atomic<bool> dead{};

    private:
        void run() override;

    public:
        ThreadMatchOptions(Player &&player, Match* match, ProtectedQueue<Match*>& not_ready_matches);

        bool options_set();

};


#endif //MICROMACHINES_THREADMATCHOPTIONS_H
