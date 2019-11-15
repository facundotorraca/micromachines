//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_BEGINLOADINGSCREEN_H
#define MICROMACHINES_BEGINLOADINGSCREEN_H

#include "Command.h"

class BeginLoadingScreen : public Command{
public:
    explicit BeginLoadingScreen(Scenario& scenario) : Command(scenario){}
    std::unique_ptr<Menu> apply() override{
        scenario.setLoadingScreen(true);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_BEGINLOADINGSCREEN_H
