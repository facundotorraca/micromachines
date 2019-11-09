//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_KEYCOMMAND_H
#define MICROMACHINES_KEYCOMMAND_H


#include <SDL_keycode.h>
#include <SDL_events.h>
#include <client/Scene.h>

class KeyCommand {
protected:
    Scene& scene;
public:
    explicit KeyCommand(Scene& scene);
    static std::unique_ptr<KeyCommand> create(Scene& scene, SDL_Keycode key, SDL_EventType type);
    virtual bool apply() = 0;
};


#endif //MICROMACHINES_KEYCOMMAND_H
