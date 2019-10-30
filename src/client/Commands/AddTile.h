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
    explicit AddTile(TileInfo info, Scenario& scenario, Bot& bot) : Command(scenario, bot), info(info){};
    void apply() override{
        scenario.addTile(info);
        bot.add_tile(info);
    }
};
#endif //MICROMACHINES_ADDTILE_H
