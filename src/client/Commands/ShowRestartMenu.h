//
// Created by javier on 14/11/19.
//

#ifndef MICROMACHINES_SHOWRESTARTMENU_H
#define MICROMACHINES_SHOWRESTARTMENU_H

#include "Command.h"
#include <client/Menu/RestartMenu.h>

class ShowRestartMenu : public Command{
public:
    explicit ShowRestartMenu(Scenario& scenario) : Command(scenario){}
    std::unique_ptr<Menu> apply() override{
        return std::unique_ptr<Menu>(new RestartMenu);
    }
};


#endif //MICROMACHINES_SHOWRESTARTMENU_H
