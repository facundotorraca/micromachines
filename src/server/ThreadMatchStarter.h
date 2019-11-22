#ifndef MICROMACHINES_THREADMATCHSTARTER_H
#define MICROMACHINES_THREADMATCHSTARTER_H

#include <atomic>
#include "common/Thread.h"
#include "server/MatchTable.h"
#include "common/ProtectedQueue.h"

class ThreadMatchStarter : public Thread {
    MatchTable& matches;
    ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches;

    std::list<std::shared_ptr<Match>>& running_matches;
    std::atomic<bool> server_running;

    private:
        void run() override;

        void close_finished_matches();

    public:
        ThreadMatchStarter(MatchTable& matches, std::list<std::shared_ptr<Match>>& running_matches, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches);

        void stop();

};

#endif //MICROMACHINES_THREADMATCHSTARTER_H

