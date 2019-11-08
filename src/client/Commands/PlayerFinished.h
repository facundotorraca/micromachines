//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_PLAYERFINISHED_H
#define MICROMACHINES_PLAYERFINISHED_H

#include "Command.h"

class PlayerFinished : public Command{
    std::string player_name;
public:
    PlayerFinished(Scenario& scenario, Bot& bot, std::string& name) : Command(scenario, bot),
    player_name(name){}
    void apply () override{
        scenario.addFinishedPlayer(player_name);
    }
};

#endif //MICROMACHINES_PLAYERFINISHED_H
