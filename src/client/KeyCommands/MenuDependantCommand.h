//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_MENUDEPENDANTCOMMAND_H
#define MICROMACHINES_MENUDEPENDANTCOMMAND_H


#include <client/Scene.h>
#include "KeyCommand.h"

class MenuDependantCommand : public KeyCommand{
protected:
    SDL_Keycode key;
    SDL_EventType event;
public:
    MenuDependantCommand(Scene &scene, SDL_Keycode key, SDL_EventType type):
    KeyCommand(scene),
    key(key), event(type){}
    bool apply() override{
        return scene.handleKeyEvent(key, event);
    }
};


#endif //MICROMACHINES_MENUDEPENDANTCOMMAND_H
