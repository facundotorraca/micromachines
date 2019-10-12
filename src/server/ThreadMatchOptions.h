#ifndef MICROMACHINES_THREADMATCHOPTIONS_H
#define MICROMACHINES_THREADMATCHOPTIONS_H

#include "Thread.h"
#include "Match.h"
#include <atomic>
#include "Player.h"

class ThreadMatchOptions : public Thread {
    std::atomic<bool> dead{};
    Player creator;
    Match* match;

    private:
        void run();

    public:
        ThreadMatchOptions(Player &&player, Match* match);

        bool options_setted();

};


#endif //MICROMACHINES_THREADMATCHOPTIONS_H
