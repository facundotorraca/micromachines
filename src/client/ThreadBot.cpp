//
// Created by aacevedo on 24/10/19.
//

#include "ThreadBot.h"


ThreadBot::ThreadBot(Bot &bot) : Thread(),
                                 bot(bot) {}

void ThreadBot::run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while (this->running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->bot.execute();
    }
}