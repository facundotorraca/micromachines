#ifndef MICROMACHINES_THREADMATCHSTARTER_H
#define MICROMACHINES_THREADMATCHSTARTER_H

#include <atomic>
#include "common/Thread.h"
#include "ThreadMatch.h"
#include "server/MatchTable.h"
#include "common/ProtectedQueue.h"

class ThreadMatchStarter : public Thread {
    MatchTable& matches;
    ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches;

    std::list<ThreadMatch*>& running_matches;
    std::atomic<bool> server_running{};

    private:
        void run();

        void close_ended_matches();

    public:
        ThreadMatchStarter(MatchTable& matches, std::list<ThreadMatch*>& running_matches, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches);

        void stop();

};

#endif //MICROMACHINES_THREADMATCHSTARTER_H
