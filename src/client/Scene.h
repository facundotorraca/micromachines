//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_SCENE_H
#define MICROMACHINES_SCENE_H

#include <SDL2/SDL.h>
#include <common/ProtectedQueue.h>
#include <map>
#include <list>
#include <client/Entities/Entity.h>
#include "ServerCommands/ServerCommand.h"
#include "Camera.h"
#include "Map.h"
#include "Scenario.h"
#include "Bot.h"
#include <client/Menu/Menu.h>

class Scene {
    Camera camera;
    ProtectedQueue<std::unique_ptr<ServerCommand>>& queue;
    Scenario scenario;
    std::unique_ptr<Menu> menu;
    std::mutex mtx;
public:

        explicit Scene(ProtectedQueue<std::unique_ptr<ServerCommand>> &queue, Bot &bot);

        bool handleKeyEvent(SDL_Keycode key, SDL_EventType type);

        void receiveMessage(ProtocolSocket& socket);

        void draw();

        void togglePause();

        void showConnectionLostMenu();

        bool quit();
};


#endif //MICROMACHINES_SCENE_H
