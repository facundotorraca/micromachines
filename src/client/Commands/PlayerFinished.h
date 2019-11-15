//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_PLAYERFINISHED_H
#define MICROMACHINES_PLAYERFINISHED_H

#include "Command.h"

class PlayerFinished : public Command{
    std::string player_name;
public:
    PlayerFinished(Scenario& scenario, std::string& name) : Command(scenario),
    player_name(name){}
    std::unique_ptr<Menu> apply () override{
        scenario.addFinishedPlayer(player_name);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_PLAYERFINISHED_H
