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

    ProtectedQueue<std::vector<int32_t>> sender_queue(10);
    Scene scene(sender_queue);

    ThreadDrawer drawer(scene);
    ThreadKeyMonitor key_monitor(scene);
    ThreadReceiver receiver(socket, scene);
    ThreadSender sender(socket, sender_queue);

    drawer.start();
    key_monitor.start();
    receiver.start();
    sender.start();

    key_monitor.join();

    sender_queue.close();
    sender.shutdown();
    sender.join();

    receiver.shutdown();
    receiver.join();

    drawer.shutdown();
    drawer.join();

    SDL_Quit();
}
