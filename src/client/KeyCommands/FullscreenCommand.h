#ifndef MICROMACHINES_FULLSCREENCOMMAND_H
#define MICROMACHINES_FULLSCREENCOMMAND_H

#include "KeyCommand.h"

class FullscreenCommand : public KeyCommand {
public:
    explicit FullscreenCommand(Scene& scene) : KeyCommand(scene){}
    bool apply() override{
        scene.toggleFullscreen();
        return true;
    }
};


#endif //MICROMACHINES_FULLSCREENCOMMAND_H
