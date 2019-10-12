#ifndef MICROMACHINES_THREADPLAYERLOCATOR_H
#define MICROMACHINES_THREADPLAYERLOCATOR_H

#include <list>
#include <atomic>
#include "Thread.h"
#include "ThreadMatch.h"
#include "ProtectedMap.h"
#include "ThreadMatchOptions.h"
#include "server/ProtectedQueue.h"
#include "ProtectedQueueMatch.h"

class ThreadPlayerLocator : public Thread {
    ProtectedMap &matches;
    ProtectedQueue &incoming_players;
    ProtectedQueueMatch& not_ready_matches;

    std::list<ThreadMatchOptions*> options_setters;
    std::atomic<bool> server_running{};

    private:
        void run() override;

        void remove_running_matches();

    public:

        explicit ThreadPlayerLocator(ProtectedQueue& incoming_players, ProtectedMap& matches, ProtectedQueueMatch& not_ready_matches);

        void stop();
};



#endif //MICROMACHINES_THREADPLAYERLOCATOR_H
