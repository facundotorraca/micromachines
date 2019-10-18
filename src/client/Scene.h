//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_SCENE_H
#define MICROMACHINES_SCENE_H


#include <SDL2/SDL.h>
#include <string>
#include <common/ProtectedQueue.h>
#include <map>
#include <client/Entities/Entity.h>

class Scene {
    ProtectedQueue<std::vector<uint8_t>>* queue;
    SDL_Window* win;
    SDL_Renderer* rend;
    std::map<uint8_t, std::unique_ptr<Entity>> entities;
    std::mutex mtx;
public:
    explicit Scene(ProtectedQueue<std::vector<uint8_t>> &queue);

    void handleKeyEvent(int key, SDL_EventType type);

    void handleServerEvent(std::vector<uint8_t>& vector);

    void draw();

    ~Scene();
};


#endif //MICROMACHINES_SCENE_H
