#include "Scene.h"
#include "Bot.h"
#include "GameMain.h"
#include <SDL2/SDL.h>
#include "ThreadDrawer.h"
#include "ThreadSender.h"
#include "ThreadReceiver.h"
#include "ThreadKeyMonitor.h"
#include "ThreadBot.h"
#include <common/ProtectedQueue.h>
#include <common/ProtocolSocket.h>
#include <memory>
#include "ServerCommands/ServerCommand.h"

GameMain::GameMain(ProtocolSocket &socket):
    socket(std::move(socket))
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
}

void GameMain::start() {
    ProtectedQueue<std::unique_ptr<ServerCommand>> sender_queue(10000);
    Bot bot(sender_queue);
    Scene scene(sender_queue, bot);

    ThreadDrawer drawer(scene);
    //ThreadBot threadBot(bot);
    ThreadKeyMonitor key_monitor(scene);
    ThreadReceiver receiver(socket, scene);
    ThreadSender sender(socket, sender_queue);

    drawer.start();
    key_monitor.start();
    //threadBot.start();
    receiver.start();
    sender.start();

    key_monitor.join();
    //threadBot.shutdown();
    //threadBot.join();
    sender_queue.close();
    sender.shutdown();
    sender.join();

    receiver.shutdown();
    receiver.join();

    drawer.shutdown();
    drawer.join();
}

GameMain::~GameMain() {
    SDL_Quit();
}
