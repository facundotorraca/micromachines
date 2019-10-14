#ifndef MICROMACHINES_THREADMATCHOPTIONS_H
#define MICROMACHINES_THREADMATCHOPTIONS_H

#include <memory>
#include "Thread.h"
#include "Match.h"
#include <atomic>
#include "Player.h"
#include "ProtectedQueue.h"

class ThreadMatchOptions : public Thread {
    ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches;

    std::shared_ptr<Match> match;
    Player creator;

    std::atomic<bool> dead{};

    private:
        void run() override;

    public:
        ThreadMatchOptions(Player &&player, std::shared_ptr<Match>&& match, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches);

        bool options_set();

};


#endif //MICROMACHINES_THREADMATCHOPTIONS_H
