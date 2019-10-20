//
// Created by javier on 19/10/19.
//

#include <iostream>
#include "ThreadUpdateSender.h"
#include "UpdateClient.h"

ThreadUpdateSender::ThreadUpdateSender(Player &player, ProtectedQueue<UpdateClient>& updates):
    player(player),
    updates(updates)
{}

void ThreadUpdateSender::run() {
    while (this->running) {
        auto update = updates.pop();
        player.send(update);
    }
}
