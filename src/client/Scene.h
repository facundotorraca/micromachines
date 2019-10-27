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

class Scene {
    ProtectedQueue<std::unique_ptr<ServerCommand>>& queue;

    Map map;
    Bot &bot;

    public:

        explicit Scene(ProtectedQueue<std::unique_ptr<ServerCommand>> &queue, Bot &bot);

        void handleServerEvent(std::vector<int32_t>& data);

        void handleKeyEvent(SDL_Keycode key, SDL_EventType type);

        void draw();
};


#endif //MICROMACHINES_SCENE_H
