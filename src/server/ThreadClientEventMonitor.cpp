#include <iostream>
#include "ThreadClientEventMonitor.h"
#include "Match.h"

ThreadClientEventMonitor::ThreadClientEventMonitor(Match* match, ProtectedQueue<UpdateRace>& updates):
    updates(updates),
    match(match)
{}

void ThreadClientEventMonitor::run() {
    while (this->running){
        try {
            auto update = updates.pop();
            match->apply_update(update);
        } catch (ProtectedQueueError& exception) {
            this->running = false;
        }
    }
}
