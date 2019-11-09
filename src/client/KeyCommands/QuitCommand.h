//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_QUITCOMMAND_H
#define MICROMACHINES_QUITCOMMAND_H


#include <client/Scene.h>
#include "KeyCommand.h"

class QuitCommand : public KeyCommand{

public:
    explicit QuitCommand(Scene &scene) : KeyCommand(scene){}
    bool apply() override{
        return scene.quit();
    }
};


#endif //MICROMACHINES_QUITCOMMAND_H
