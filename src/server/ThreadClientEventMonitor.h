#ifndef MICROMACHINES_THREADCLIENTEVENTMONITOR_H
#define MICROMACHINES_THREADCLIENTEVENTMONITOR_H

#include <common/ProtectedQueue.h>
#include "UpdateRace.h"
#include <common/Thread.h>

class Match;

class ThreadClientEventMonitor : public Thread {
    ProtectedQueue<UpdateRace>& updates;
    Match* match;

    std::atomic<bool> restart_mode;

    private:
        void run() override;

    public:
        ThreadClientEventMonitor(Match* match, ProtectedQueue<UpdateRace>& updates);

        void set_on_running_game_mode();

        void set_on_restart_mode();
};


#endif //MICROMACHINES_THREADCLIENTEVENTMONITOR_H
