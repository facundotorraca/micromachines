//
// Created by javier on 16/10/19.
//

#include <common/ProtocolSocket.h>
#include <common/SocketError.h>
#include "ThreadReceiver.h"
#include "Scene.h"

ThreadReceiver::ThreadReceiver(ProtocolSocket& socket, Scene& scene) : scene(&scene), socket(&socket){}

void ThreadReceiver::run() {
    while (running) {
        std::vector<int32_t> buffer;
        try {
            this->socket->receive(buffer);
            this->scene->handleServerEvent(buffer);
        } catch (SocketError& e) {
            running = false;
        }
    }
}
