#ifndef MICROMACHINES_THREADPLAYERLOCATOR_H
#define MICROMACHINES_THREADPLAYERLOCATOR_H

#include <list>
#include <memory>
#include <atomic>
#include "Thread.h"
#include "Player.h"
#include "ThreadMatch.h"
#include "MatchTable.h"
#include "ThreadMatchOptions.h"
#include "server/ProtectedQueue.h"

class ThreadPlayerLocator : public Thread {
    MatchTable& matches;
    ProtectedQueue<Player>& incoming_players;
    ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches;

    std::list<ThreadMatchOptions*> options_setters;
    std::atomic<bool> server_running{};

    private:
        void run() override;

        void remove_running_matches();

    public:
        explicit ThreadPlayerLocator(ProtectedQueue<Player>& incoming_players, MatchTable& matches, ProtectedQueue<std::shared_ptr<Match>>& not_ready_matches);

        void stop();
};



#endif //MICROMACHINES_THREADPLAYERLOCATOR_H
