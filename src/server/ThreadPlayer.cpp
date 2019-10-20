//
// Created by facundotorraca on 19/10/19.
//

#include "ThreadPlayer.h"
#include "ThreadUpdateSender.h"

ThreadPlayer::ThreadPlayer(ProtectedQueue<UpdateClient> &updates_send, ProtectedQueue<UpdateRace> &updates_recv, Player &player) :
    sender(player, updates_send),
    updates_send(updates_send),
    updates_recv(updates_recv),
    player(player)
{}

void ThreadPlayer::run() {
    this->sender.start();
    while (this->running) {
        auto data = player.receive_update();
        updates_recv.push(data);
    }
    this->sender.shutdown();
    this->sender.join();
}
