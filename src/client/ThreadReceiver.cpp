//
// Created by javier on 16/10/19.
//

#include <common/ProtocolSocket.h>
#include "ThreadReceiver.h"
#include "Scene.h"

ThreadReceiver::ThreadReceiver(ProtocolSocket& socket, Scene& scene) : scene(&scene), socket(&socket){}

void ThreadReceiver::run() {
    std::vector<uint8_t> buffer;
    auto running = true;
    while (running) {
        this->socket->receive(buffer);
        this->scene->handleServerEvent(buffer);
    }
}
