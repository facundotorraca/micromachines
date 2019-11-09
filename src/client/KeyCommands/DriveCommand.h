//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_DRIVECOMMAND_H
#define MICROMACHINES_DRIVECOMMAND_H


#include <client/Scene.h>
#include "KeyCommand.h"

class DriveCommand : public KeyCommand{
protected:
    SDL_Keycode key;
    SDL_EventType event;
public:
    DriveCommand(Scene &scene, SDL_Keycode key, SDL_EventType type):
    KeyCommand(scene),
    key(key), event(type){}
    bool apply() override{
        scene.handleKeyEvent(key, event);
        return true;
    }
};


#endif //MICROMACHINES_DRIVECOMMAND_H
