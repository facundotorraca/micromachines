#include <iostream>
#include "UpdateClient.h"
#include <common/SocketError.h>
#include "ThreadUpdateSender.h"

ThreadUpdateSender::ThreadUpdateSender(Player &player, ClientUpdater& client_updater):
    player(player),
    client_updater(client_updater)
{}

void ThreadUpdateSender::run() {
    try {
        int32_t ID = player.get_ID();
        while (this->running) {
            auto update = client_updater.get_update(ID);
            player.send(update);
        }
    } catch (const ProtectedQueueError& exception) {
        this->running = false;
    } catch (const SocketError& exception) {
        this->running = false;
    }
}