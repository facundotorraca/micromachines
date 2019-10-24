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
#include "Camera.h"
#include "Map.h"

class Scene {
    ProtectedQueue<std::vector<int32_t>>& queue;

    Map map;

    public:

        explicit Scene(ProtectedQueue<std::vector<int32_t>> &queue);

        void handleServerEvent(std::vector<int32_t>& data);

        void handleKeyEvent(int key, SDL_EventType type);

        void draw();
};


#endif //MICROMACHINES_SCENE_H
