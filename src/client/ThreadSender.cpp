//
// Created by javier on 16/10/19.
//

#include <common/ProtectedQueue.h>
#include "ThreadSender.h"

ThreadSender::ThreadSender(ProtocolSocket& socket, ProtectedQueue<std::unique_ptr<ServerCommand>>& queue):
    socket(socket),
    queue(queue)
{}

void ThreadSender::run() {
    while (this->running) {
        try {
            auto data = queue.pop();
            data->send(socket);
        } catch (ProtectedQueueError& e) {
            this->running = false;
        }
    }
}
