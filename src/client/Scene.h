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
#include <client/Commands/Command.h>
#include "ServerCommands/ServerCommand.h"
#include "Camera.h"
#include "Map.h"
#include "Scenario.h"

class Scene {
    ProtectedQueue<std::unique_ptr<ServerCommand>>& queue;
    Scenario scenario;
    Bot &bot;

    public:

        explicit Scene(ProtectedQueue<std::unique_ptr<ServerCommand>> &queue, Bot &bot);

        bool handleKeyEvent(SDL_Keycode key, SDL_EventType type);

        std::unique_ptr<Command> receiveMessage(ProtocolSocket& socket);

        void draw();

        void togglePause();

        void showConnectionLostMenu();

        bool quit();
};


#endif //MICROMACHINES_SCENE_H
