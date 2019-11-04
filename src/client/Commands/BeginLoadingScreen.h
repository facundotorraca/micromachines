//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_BEGINLOADINGSCREEN_H
#define MICROMACHINES_BEGINLOADINGSCREEN_H

#include "Command.h"

class BeginLoadingScreen : public Command{
public:
    BeginLoadingScreen(Scenario& scenario, Bot& bot) : Command(scenario, bot){}
    void apply() override{
        scenario.setLoadingScreen(true);
    }
};

#endif //MICROMACHINES_BEGINLOADINGSCREEN_H
