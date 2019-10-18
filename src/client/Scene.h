//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_SCENE_H
#define MICROMACHINES_SCENE_H


#include <SDL2/SDL.h>
#include <string>
#include <common/ProtectedQueue.h>
#include <map>
#include <list>
#include <client/Entities/Entity.h>

class Scene {
    ProtectedQueue<std::vector<int32_t>>* queue;
    SDL_Window* win;
    SDL_Renderer* rend;
    std::list<std::unique_ptr<Entity>> background;
    std::map<uint8_t, std::unique_ptr<Entity>> entities;
    std::mutex mtx;
    uint8_t my_car_id;
    SDL_Point camera{};
    void updateEntity(std::vector<int32_t> &vector);
    void setMyCarID(std::vector<int32_t>& vector);
    void setMap(std::vector<int32_t>& vector);
public:

    explicit Scene(ProtectedQueue<std::vector<int32_t>> &queue);

    void handleKeyEvent(int key, SDL_EventType type);

    void handleServerEvent(std::vector<int32_t>& vector);

    void draw();

    ~Scene();
};


#endif //MICROMACHINES_SCENE_H
