//
// Created by alejoacevedo on 11/10/19.
//

#include "ThreadPluging.h"

ThreadPluging::ThreadPluging(PlugingsManager &plugingsManager) : Thread(),
                                                                 plugingsManager(plugingsManager) {}

void ThreadPluging::run() {
    this->plugingsManager.load_plugings();
    while (this->running) {
        this->plugingsManager.execute();
        std::this_thread::sleep_for(std::chrono::milliseconds(333));
    }
}