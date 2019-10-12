#ifndef MICROMACHINES_THREADMATCH_H
#define MICROMACHINES_THREADMATCH_H

#include "Thread.h"
#include "Match.h"
#include <atomic>

class ThreadMatch : public Thread {
    std::atomic<bool> dead;
    Match* match;

    private:
        void run() override;

    public:
        explicit ThreadMatch(Match *match);

        bool is_running();
};


#endif //MICROMACHINES_THREADMATCH_H
