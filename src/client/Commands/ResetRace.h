//
// Created by javier on 14/11/19.
//

#ifndef MICROMACHINES_RESETRACE_H
#define MICROMACHINES_RESETRACE_H


#include <client/Scenario.h>
#include <client/Menu/NoMenu.h>
#include "Command.h"

class ResetRace : public Command {
public:
    explicit ResetRace(Scenario &scenario) : Command(scenario){}
    std::unique_ptr<Menu> apply(){
        scenario.reset();
        return std::unique_ptr<Menu>(new NoMenu);
    }
};


#endif //MICROMACHINES_RESETRACE_H
