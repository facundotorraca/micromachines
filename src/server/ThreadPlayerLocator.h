#ifndef MICROMACHINES_THREADPLAYERLOCATOR_H
#define MICROMACHINES_THREADPLAYERLOCATOR_H

#include <list>
#include <memory>
#include <atomic>
#include "common/Thread.h"
#include "server/Player.h"
#include "ThreadMatch.h"
#include "server/MatchTable.h"
#include "ThreadMatchOptions.h"
#include "common/ProtectedQueue.h"

class ThreadPlayerLocator : public Thread {
    MatchTable& matches;
    ProtectedQueue<Player>& incoming_players;
    ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches;

    std::list<ThreadMatchOptions*> options_setters;
    std::atomic<bool> server_running{};

    private:
        void run() override;

        void kill_all_setter();

        void remove_running_matches();

    public:
        explicit ThreadPlayerLocator(ProtectedQueue<Player>& incoming_players, MatchTable& matches, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches);

        void stop();
};



#endif //MICROMACHINES_THREADPLAYERLOCATOR_H
