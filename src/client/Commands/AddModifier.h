//
// Created by javif on 30/10/2019.
//

#ifndef MICROMACHINES_ADDMODIFIER_H
#define MICROMACHINES_ADDMODIFIER_H

#include "Command.h"

class AddModifier : public Command{
    int32_t type;
    int32_t posx;
    int32_t posy;
public:
    explicit AddModifier(Scenario& scenario, int32_t type, int32_t x, int32_t y):
        Command(scenario),
        type(type),
        posx(x),
        posy(y){}

    std::unique_ptr<Menu> apply() override {
        scenario.addModifier(type, posx, posy);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_ADDMODIFIER_H
