//
// Created by javier on 19/10/19.
//

#include <iostream>
#include "UpdateClient.h"
#include <common/SocketError.h>
#include "ThreadUpdateSender.h"

ThreadUpdateSender::ThreadUpdateSender(Player &player, ProtectedQueue<UpdateClient>& updates):
    player(player),
    updates(updates)
{}

void ThreadUpdateSender::run() {
    try {
        while (this->running) {
            auto update = updates.pop();
            player.send(update);
        }
    } catch (const ProtectedQueueError& exception) {
        this->running = false;
    } catch (const SocketError& exception) {
        this->running = false;
    }
}