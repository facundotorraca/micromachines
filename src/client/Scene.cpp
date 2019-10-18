//
// Created by javier on 16/10/19.
//

#include <SDL2/SDL.h>
#include <vector>
#include "Scene.h"
#include <common/EntityType.h>
#include <client/Entities/Car.h>
#include <common/Key.h>

void Scene::handleKeyEvent(SDL_Keycode key, SDL_EventType type) {

    int k = 0;
    int e = 0;

    switch (key) {
        case SDLK_DOWN:
            k = KEY_DOWN;
            break;
        case SDLK_LEFT:
            k = KEY_LEFT;
            break;
        case SDLK_RIGHT:
            k = KEY_RIGHT;
            break;
        case SDLK_UP:
            k = KEY_UP;
            break;
    }

    switch (type) {
        case (SDL_KEYDOWN):
            e = KEY_PRESSED;
            break;
        case (SDL_KEYUP):
            e = KEY_RELEASED;
            break;
    }

    auto vec = std::vector<uint8_t>();
    vec.emplace_back(k);
    vec.emplace_back(e);
    queue->push(vec);
}

void Scene::handleServerEvent(std::vector<uint8_t>& vector) {
    uint8_t id = vector[0];
    uint8_t type = vector[1];
    uint8_t posX = vector[2];
    uint8_t posY = vector[3];
    uint8_t rot = vector[4];

    try {
        auto& entity = entities.at(id);
    } catch (std::exception& e) {
        entities.emplace(id, new Car(rend));
    }

    entities[id]->update(posX, posY, rot);
}

void Scene::draw() {
    SDL_RenderClear(rend);
    for (const auto& entity : entities) {
        entity.second->draw();
    }
    SDL_RenderPresent(rend);
}

Scene::Scene(ProtectedQueue<std::vector<uint8_t>> &queue) : queue(&queue), win(nullptr),
        rend(nullptr){
    SDL_CreateWindowAndRenderer(800, 600, 0, &win, &rend);
}

Scene::~Scene() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}
