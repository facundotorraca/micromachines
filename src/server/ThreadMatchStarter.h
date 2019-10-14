#ifndef MICROMACHINES_THREADMATCHSTARTER_H
#define MICROMACHINES_THREADMATCHSTARTER_H

#include <atomic>
#include "Thread.h"
#include "ThreadMatch.h"
#include "MatchTable.h"
#include "ProtectedQueue.h"

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



};

#endif //MICROMACHINES_THREADMATCHSTARTER_H
