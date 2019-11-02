#include <common/SocketError.h>
#include "ThreadPlayer.h"
#include "ThreadUpdateSender.h"

ThreadPlayer::ThreadPlayer(ProtectedQueue<UpdateClient> &updates_send, ProtectedQueue<UpdateRace> &updates_recv, Player &player) :
    sender(player, updates_send),
    updates_send(updates_send),
    updates_recv(updates_recv),
    player(player),
    player_on_hold(true)
{}

void ThreadPlayer::run() {
    this->sender.start();
    try {
        while (this->running) {
            auto data = player.receive_update();
            if (!player_on_hold)
                updates_recv.push(data);
        }
    } catch (const SocketError& exception) {
        this->stop();
    } catch (const ProtectedQueueError& exception) {
        this->stop();
    }
}

void ThreadPlayer::stop() {
    updates_send.close();
    this->sender.shutdown();
    this->sender.join();
    this->running = false;
}

void ThreadPlayer::set_player_on_hold() {
    this->player_on_hold = true;
}

void ThreadPlayer::wake_up() {
    this->player_on_hold = false;
}
