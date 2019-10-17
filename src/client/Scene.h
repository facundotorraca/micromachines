//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_SCENE_H
#define MICROMACHINES_SCENE_H


#include <SDL2/SDL_events.h>

class Scene {

public:
    void handleKeyEvent(int key, SDL_EventType type);

    void handleServerEvent(std::vector<uint8_t>& vector);

    void draw();
};


#endif //MICROMACHINES_SCENE_H
