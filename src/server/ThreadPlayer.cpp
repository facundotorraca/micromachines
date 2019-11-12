#include "ThreadPlayer.h"
#include "ClientUpdater.h"
#include "ThreadUpdateSender.h"
#include <common/SocketError.h>

ThreadPlayer::ThreadPlayer(ClientUpdater& client_updater, ProtectedQueue<UpdateRace> &updates_recv, Player &player) :
    sender(player, client_updater),
    client_updater(client_updater),
    updates_recv(updates_recv),
    player(player),
    on_hold(false)
{}

void ThreadPlayer::run() {
    this->sender.start();
    try {
        while (this->running) {
            auto data = player.receive_update();
            if (!this->on_hold)
                updates_recv.push(data);
        }
    } catch (const SocketError& exception) {
        this->stop();
    } catch (const ProtectedQueueError& exception) {
        this->stop();
    }
}

void ThreadPlayer::stop() {
    this->client_updater.close_queue(this->player.get_ID());
    this->sender.shutdown();
    this->sender.join();
    this->running = false;
}

void ThreadPlayer::set_on_hold() {
    this->on_hold = true;
}

void ThreadPlayer::resume() {
    this->on_hold = false;
}
