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

class Scene {
    ProtectedQueue<std::vector<int32_t>>& queue;

    SDL_Window* win;
    SDL_Renderer* rend;

    Camera camera;

    public:

        explicit Scene(ProtectedQueue<std::vector<int32_t>> &queue);

        void handleServerEvent(std::unique_ptr<Command> command);

        void handleKeyEvent(int key, SDL_EventType type);

        void draw();

        ~Scene();
};


#endif //MICROMACHINES_SCENE_H
