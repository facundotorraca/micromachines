//
// Created by javier on 16/10/19.
//

#include <common/ProtocolSocket.h>
#include <common/ProtectedQueue.h>
#include <SDL2/SDL.h>
#include "GameMain.h"
#include "Scene.h"
#include "ThreadDrawer.h"
#include "ThreadKeyMonitor.h"
#include "ThreadSender.h"
#include "ThreadReceiver.h"

GameMain::GameMain(ProtocolSocket &socket) : socket(std::move(socket)) {}

void GameMain::start() {
    SDL_Init(SDL_INIT_VIDEO);

    ProtectedQueue<std::vector<uint8_t>> sender_queue(10);
    Scene scene(sender_queue);

    ThreadDrawer drawer(scene);
    ThreadKeyMonitor key_monitor(scene);
    ThreadReceiver receiver(socket, scene);
    ThreadSender sender(socket, sender_queue);

    drawer.run();
    key_monitor.run();
    receiver.run();
    sender.run();

    sender.join();
    receiver.join();
    key_monitor.join();
    drawer.join();

    SDL_Quit();
}
