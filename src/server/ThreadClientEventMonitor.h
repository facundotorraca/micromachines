//
// Created by javier on 19/10/19.
//

#ifndef MICROMACHINES_THREADCLIENTEVENTMONITOR_H
#define MICROMACHINES_THREADCLIENTEVENTMONITOR_H

#include <common/ProtectedQueue.h>
#include "UpdateRace.h"
#include <common/Thread.h>

class Match;

class ThreadClientEventMonitor : public Thread {
    ProtectedQueue<UpdateRace>& updates;
    Match* match;
private:
    void run() override;
public:
    ThreadClientEventMonitor(Match* match, ProtectedQueue<UpdateRace>& updates);
};


#endif //MICROMACHINES_THREADCLIENTEVENTMONITOR_H
