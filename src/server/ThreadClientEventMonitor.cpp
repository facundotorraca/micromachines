#include "ThreadClientEventMonitor.h"
#include "Match.h"

ThreadClientEventMonitor::ThreadClientEventMonitor(Match* match, ProtectedQueue<UpdateRace>& updates):
    restart_mode(false),
    updates(updates),
    match(match)
{}

void ThreadClientEventMonitor::run() {
    while (this->running){
        try {
            auto update = updates.pop();

            if (!this->restart_mode)
                match->apply_update(update);
            else
                match->set_restart_option(update);

        } catch (ProtectedQueueError& exception) {
            this->running = false;
        }
    }
}

void ThreadClientEventMonitor::set_on_restart_mode() {
    this->restart_mode = true;
}

void ThreadClientEventMonitor::set_on_running_game_mode() {
    this->restart_mode = false;
}
