//
// Created by javier on 16/10/19.
//

#include <common/ProtocolSocket.h>
#include <common/SocketError.h>
#include <client/Commands/Command.h>
#include "ThreadReceiver.h"
#include "Scene.h"

ThreadReceiver::ThreadReceiver(ProtocolSocket& socket, Scene& scene) : scene(scene), socket(socket){}

void ThreadReceiver::run() {
    while (this->running) {
        std::vector<int32_t> buffer;
        try {
            int i = 0;
            this->socket.receive(buffer);
            i++;
            std::cout << "recibi " << i << "\n";
            this->scene.handleServerEvent(buffer);
        } catch (SocketError& e) {
            this->running = false;
        }
    }
}
