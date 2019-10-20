#include <iostream>
#include "ThreadClientEventMonitor.h"
#include "Match.h"

ThreadClientEventMonitor::ThreadClientEventMonitor(Match* match, ProtectedQueue<UpdateRace>& updates):
    match(match),
    updates(updates)
{}

void ThreadClientEventMonitor::run() {
    while (this->running){
        auto update = updates.pop();
        match->apply_update(update);
    }
}
