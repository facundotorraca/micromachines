#include "Scene.h"
#include "GameMain.h"
#include <SDL2/SDL.h>
#include "ThreadDrawer.h"
#include "ThreadSender.h"
#include "ThreadReceiver.h"
#include "ThreadKeyMonitor.h"
#include <common/ProtectedQueue.h>
#include <common/ProtocolSocket.h>
#include <memory>
#include "ServerCommands/ServerCommand.h"

GameMain::GameMain(ProtocolSocket &socket):
    socket(std::move(socket))
{}

void GameMain::start() {
    SDL_Init(SDL_INIT_VIDEO);

    ProtectedQueue<std::unique_ptr<ServerCommand>> sender_queue(10000);
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
