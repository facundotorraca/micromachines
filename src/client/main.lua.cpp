//
// Created by aacevedo on 24/10/19.
//

#include <iostream>
#include "Bot.h"
#include <common/ProtectedQueue.h>

int main(int argc, char *argv[]) {
    ProtectedQueue<std::unique_ptr<ServerCommand>> queue(10000);
    Bot bot(queue);
    bot.execute();
    auto v = queue.pop();
}