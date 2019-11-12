//
// Created by javier on 16/10/19.
//

#include <common/ProtocolSocket.h>
#include <common/SocketError.h>
#include "ThreadReceiver.h"
#include "Scene.h"

ThreadReceiver::ThreadReceiver(ProtocolSocket& socket, Scene& scene) : scene(scene), socket(socket){}

void ThreadReceiver::run() {
    while (this->running) {
        std::vector<int32_t> buffer;
        try {
            this->scene.receiveMessage(socket);
        } catch (SocketError& e) {
            this->scene.showConnectionLostMenu();
            this->running = false;
        }
    }
}
