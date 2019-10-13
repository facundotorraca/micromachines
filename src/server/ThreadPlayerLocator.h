#ifndef MICROMACHINES_THREADPLAYERLOCATOR_H
#define MICROMACHINES_THREADPLAYERLOCATOR_H

#include <list>
#include <atomic>
#include "Thread.h"
#include "Player.h"
#include "ThreadMatch.h"
#include "ProtectedMap.h"
#include "ThreadMatchOptions.h"
#include "ProtectedQueueMatch.h"
#include "server/ProtectedQueue.h"

class ThreadPlayerLocator : public Thread {
    ProtectedMap &matches;
    ProtectedQueue<Player> &incoming_players;
    ProtectedQueueMatch& not_ready_matches;

    std::list<ThreadMatchOptions*> options_setters;
    std::atomic<bool> server_running{};

    private:
        void run() override;

        void remove_running_matches();

    public:

        explicit ThreadPlayerLocator(ProtectedQueue<Player>& incoming_players, ProtectedMap& matches, ProtectedQueueMatch& not_ready_matches);

        void stop();
};



#endif //MICROMACHINES_THREADPLAYERLOCATOR_H
