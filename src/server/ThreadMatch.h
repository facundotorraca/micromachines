#ifndef MICROMACHINES_THREADMATCH_H
#define MICROMACHINES_THREADMATCH_H

#include <atomic>
#include <memory>
#include "Match.h"
#include "Thread.h"

class ThreadMatch : public Thread {
    std::shared_ptr<Match> match;
    std::atomic<bool> dead;

    private:
        void run() override;

    public:
        explicit ThreadMatch(std::shared_ptr<Match>&& match);

        bool is_running();

        void stop();
};


#endif //MICROMACHINES_THREADMATCH_H
