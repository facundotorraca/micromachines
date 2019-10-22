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
#include <client/Commands/Command.h>

class Scene {
    ProtectedQueue<std::vector<int32_t>>& queue;

    SDL_Window* win;
    SDL_Renderer* rend;

    std::list<std::unique_ptr<Entity>> background;
    std::map<uint8_t, std::unique_ptr<Entity>> entities;
    std::mutex mtx;

    int32_t my_car_ID;
    Camera camera{};

    private:
        void updateEntity(std::vector<int32_t> &update_info);

        void setMyCarID(std::vector<int32_t>& vector);

        void setMap(std::vector<int32_t>& vector);

    public:

        explicit Scene(ProtectedQueue<std::vector<int32_t>> &queue);

        void handleServerEvent(std::unique_ptr<Command> command);

        void handleKeyEvent(int key, SDL_EventType type);

        void draw();

        ~Scene();
};


#endif //MICROMACHINES_SCENE_H
