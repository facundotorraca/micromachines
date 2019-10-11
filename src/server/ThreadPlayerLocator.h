#ifndef MICROMACHINES_THREADPLAYERLOCATOR_H
#define MICROMACHINES_THREADPLAYERLOCATOR_H

#include <list>
#include "ProtectedMap.h"
#include "ProtectedQueue.h"
#include "ThreadMatch.h"

class ThreadPlayerLocator {
    std::thread thread{};
    ProtectedMap& lobbies;
    ProtectedQueue& incoming_players;
    std::list<ThreadMatch*>& matches;

    private:
        void run();

    public:
        explicit ThreadPlayerLocator(ProtectedQueue& incoming_players, ProtectedMap& lobbies, std::list<ThreadMatch*>& matches);

        static void stop();

        void join();

        void start();
};

#endif //MICROMACHINES_THREADPLAYERLOCATOR_H
