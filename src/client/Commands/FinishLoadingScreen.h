//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_FINISHLOADINGSCREEN_H
#define MICROMACHINES_FINISHLOADINGSCREEN_H

#include "Command.h"

class FinishLoadingScreen : public Command{
public:
    FinishLoadingScreen(Scenario& scenario) : Command(scenario){}
    std::unique_ptr<Menu> apply() override{
        scenario.setLoadingScreen(false);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_FINISHLOADINGSCREEN_H
