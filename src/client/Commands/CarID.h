//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_CARID_H
#define MICROMACHINES_CARID_H

#include "Command.h"

class CarID : public Command {
    int32_t id;
public:
    explicit CarID(int32_t id) : id(id){}
    void apply(Camera& camera) override {
        camera.setOwnID(id);
    }
};

#endif //MICROMACHINES_CARID_H
