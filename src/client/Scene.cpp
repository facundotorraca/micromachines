#include <vector>
#include "Scene.h"
#include <SDL2/SDL.h>
#include <common/Key.h>
#include "Entities/Car.h"
#include "Entities/Track.h"
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define INVALIDAD_CAD_ID -1

#define MESSAGE_TYPE_POS 0
#define ENTITY_ID_POS 1
#define TYPE_UPDATE_POS 2
#define X_POS 3
#define Y_POS 4
#define ANGLE_POS 5

Scene::Scene(ProtectedQueue<std::vector<int32_t>>& queue):
        queue(queue),
        win(nullptr),
        rend(nullptr)
{
    this->my_car_ID = INVALIDAD_CAD_ID;
    SDL_CreateWindowAndRenderer(1280, 720, 0, &win, &rend);
}

void Scene::handleKeyEvent(SDL_Keycode key, SDL_EventType type) {
    auto key_event = std::vector<int32_t>();

    switch (key) {
        case SDLK_DOWN:
            key_event.push_back(KEY_DOWN);
            break;
        case SDLK_LEFT:
            key_event.push_back(KEY_LEFT);
            break;
        case SDLK_RIGHT:
            key_event.push_back(KEY_RIGHT);
            break;
        case SDLK_UP:
            key_event.push_back(KEY_UP);
            break;
        default:
            break;
    }

    switch (type) {
        case (SDL_KEYDOWN):
            key_event.push_back(KEY_PRESSED);
            break;
        case (SDL_KEYUP):
            key_event.push_back(KEY_RELEASED);
            break;
        default:
            break;
    }

    queue.push(key_event);
}

void Scene::updateEntity(std::vector<int32_t>& update_info){
    int32_t entity_ID = update_info[ENTITY_ID_POS];
    int32_t type = update_info[TYPE_UPDATE_POS];
    int32_t pos_x = update_info[X_POS];
    int32_t pos_y = update_info[Y_POS];
    int32_t angle = update_info[ANGLE_POS];

    // My car should be the first entity I receive
    if (entities.empty())
        this->my_car_ID = entity_ID;

    // If this is my car, update camera
    if (entity_ID == my_car_ID){
        camera.x = pos_x;
        camera.y = pos_y;
    }

    std::unique_lock<std::mutex> lock(this->mtx);
    try {
        entities.at(entity_ID);
    } catch (std::exception& e) {
        switch (type) {
            case TYPE_CAR:
                entities.emplace(entity_ID, new Car(rend));
                break;
            default:
                break;
        }
    }
    entities[entity_ID]->update(pos_x, pos_y, angle);
}

void Scene::setMap(std::vector<int32_t> &vector) {
    background.emplace_back(new Track(rend, vector[ENTITY_ID_POS]));
}

void Scene::setMyCarID(std::vector<int32_t> &vector) {
    my_car_ID = vector[ENTITY_ID_POS];
}

void Scene::handleServerEvent(std::vector<int32_t>& message) {
    int32_t msg_type = message[MESSAGE_TYPE_POS];

    switch (msg_type) {
        case MSG_UPDATE_ENTITY:
            updateEntity(message);
            break;
        case MSG_TRACK_ID:
            setMap(message);
            break;
        case MSG_CAR_ID:
            setMyCarID(message);
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

Scene::~Scene() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}
