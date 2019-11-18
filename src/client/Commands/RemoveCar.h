//
// Created by javier on 18/11/19.
//

#ifndef MICROMACHINES_REMOVECAR_H
#define MICROMACHINES_REMOVECAR_H


#include <client/Scenario.h>
#include "Command.h"

class RemoveCar : public Command {
    int32_t id;
public:
    RemoveCar(Scenario &scenario, int32_t id) : Command(scenario), id(id) {

    }
    std::unique_ptr<Menu> apply () override{
        scenario.removeCar(id);
        return std::unique_ptr<Menu>();
    }
};


#endif //MICROMACHINES_REMOVECAR_H
