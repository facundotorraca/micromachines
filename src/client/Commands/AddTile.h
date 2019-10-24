//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_ADDTILE_H
#define MICROMACHINES_ADDTILE_H

#include "Command.h"
#include "TileInfo.h"
#include <client/Camera.h>

class AddTile : public Command {
    TileInfo info;
public:
    explicit AddTile(TileInfo info) : info(info){};
    void apply(Camera& camera) override{
        camera.addTile(info);
    }
};
#endif //MICROMACHINES_ADDTILE_H
