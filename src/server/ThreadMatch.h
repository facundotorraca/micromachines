#ifndef MICROMACHINES_THREADMATCH_H
#define MICROMACHINES_THREADMATCH_H

#include <thread>
#include "Player.h"
#include "ProtectedList.h"

class ThreadMatch {
    std::thread thread{};
    ProtectedList* lobby;

    private:
        void run();

    public:
        explicit ThreadMatch(ProtectedList* lobby);

        void start();
};

#endif //MICROMACHINES_THREADMATCH_H

