//
// Created by javier on 16/10/19.
//

#include <common/ProtectedQueue.h>
#include "ThreadSender.h"

ThreadSender::ThreadSender(ProtocolSocket& socket, ProtectedQueue<std::vector<int32_t>>& queue):
    socket(&socket),
    queue(&queue)
{}

void ThreadSender::run() {
    while (running) {
        try {
            auto data = queue->pop();
            socket->send(data);
        } catch (ProtectedQueueError& e) {
            running = false;
        }
    }
}
