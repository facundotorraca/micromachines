//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_PAUSECOMMAND_H
#define MICROMACHINES_PAUSECOMMAND_H


#include <client/Scene.h>
#include "KeyCommand.h"

class PauseCommand : public KeyCommand {

public:
    PauseCommand(Scene &scene) : KeyCommand(scene) {}
    bool apply() override{
        scene.togglePause();
        return true;
    }

};
#endif //MICROMACHINES_PAUSECOMMAND_H
