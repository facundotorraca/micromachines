//
// Created by aacevedo on 24/10/19.
//

#include <iostream>
#include "Bot.h"
#include <common/ProtectedQueue.h>

int main(int argc, char *argv[]) {
    ProtectedQueue<std::vector<int32_t>> queue(10000);
    Bot bot(queue);
    bot.execute();
    auto v = queue.pop();
    std::cout << v.at(0) << " , " << v.at(1) << std::endl;
}