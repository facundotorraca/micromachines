//
// Created by javier on 24/10/19.
//

#ifndef MICROMACHINES_ADDTILE_H
#define MICROMACHINES_ADDTILE_H

#include "Command.h"
#include "client/Entities/TileInfo.h"
#include <client/Camera.h>

class AddTile : public Command {
    TileInfo info;
public:
    explicit AddTile(TileInfo info, Scenario& scenario) : Command(scenario), info(info){};
    std::unique_ptr<Menu> apply() override{
        scenario.addTile(info);
        return std::unique_ptr<Menu>();
    }
};
#endif //MICROMACHINES_ADDTILE_H
