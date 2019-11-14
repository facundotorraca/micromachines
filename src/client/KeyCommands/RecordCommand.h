//
// Created by javier on 13/11/19.
//

#ifndef MICROMACHINES_RECORDCOMMAND_H
#define MICROMACHINES_RECORDCOMMAND_H


#include "KeyCommand.h"

class RecordCommand : public KeyCommand {
public:
    explicit RecordCommand(Scene& scene) : KeyCommand(scene){}
    bool apply() override{
        scene.toggleRecording();
        return true;
    }
};


#endif //MICROMACHINES_RECORDCOMMAND_H
