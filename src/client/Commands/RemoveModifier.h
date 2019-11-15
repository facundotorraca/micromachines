//
// Created by javif on 30/10/2019.
//

#ifndef MICROMACHINES_REMOVEMODIFIER_H
#define MICROMACHINES_REMOVEMODIFIER_H

#include "Command.h"

class RemoveModifier : public Command{
    int32_t posx;
    int32_t posy;
public:
    explicit RemoveModifier(Scenario& scenario, int32_t x, int32_t y):
        Command(scenario),
        posx(x),
        posy(y){}

    std::unique_ptr<Menu> apply() override {
        scenario.removeModifier(posx, posy);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_REMOVEMODIFIER_H
