//
// Created by javier on 16/10/19.
//

#include <SDL2/SDL.h>
#include <vector>
#include "Scene.h"
#include "Entities/Car.h"
#include "Entities/Track.h"
#include <common/EntityType.h>
#include <common/Key.h>
#include <common/MsgTypes.h>

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
        default:
            break;
    }

    switch (type) {
        case (SDL_KEYDOWN):
            e = KEY_PRESSED;
            break;
        case (SDL_KEYUP):
            e = KEY_RELEASED;
            break;
        default:
            break;
    }

    auto vec = std::vector<int32_t>();
    vec.emplace_back(k);
    vec.emplace_back(e);
    queue->push(vec);
}

void Scene::updateEntity(std::vector<int32_t>& vector){
    int32_t id = vector[1];
    int32_t type = vector[2];
    int32_t posX = vector[3];
    int32_t posY = vector[4];
    int32_t rot = vector[5];

    // My car should be the first entity I receive
    if (entities.empty())
        this->my_car_id = id;

    // If this is my car, update camera
    if (id == my_car_id){
        camera.x = posX;
        camera.y = posY;
    }

    std::unique_lock<std::mutex> lock(mtx);
    try {
        entities.at(id);
    } catch (std::exception& e) {
        switch (type) {
            case TYPE_CAR:
                entities.emplace(id, new Car(rend));
                break;
            default:
                break;
        }
    }
    entities[id]->update(posX, posY, rot);
}

void Scene::setMap(std::vector<int32_t> &vector) {
    background.emplace_back(new Track(rend, vector.at(1)));
}

void Scene::setMyCarID(std::vector<int32_t> &vector) {
    my_car_id = vector.at(1);
}

void Scene::handleServerEvent(std::vector<int32_t>& vector) {
    uint8_t msgtype = vector.at(0);
    switch (msgtype){
        case MSG_UPDATE_ENTITY:
            updateEntity(vector);
            break;
        case MSG_TRACK_ID:
            setMap(vector);
            break;
        case MSG_CAR_ID:
            setMyCarID(vector);
            break;
        default:
            break;
    }
}

void Scene::draw() {
    std::unique_lock<std::mutex> lock(mtx);
    SDL_RenderClear(rend);
    for (const auto& staticentity : background){
        staticentity->draw(camera);
    }
    for (const auto& entity : entities) {
        entity.second->draw(camera);
    }
    SDL_RenderPresent(rend);
}

Scene::Scene(ProtectedQueue<std::vector<int32_t>> &queue) : queue(&queue), win(nullptr),
        rend(nullptr), mtx(), my_car_id(0){
    SDL_CreateWindowAndRenderer(1280, 720, 0, &win, &rend);
}

Scene::~Scene() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}
