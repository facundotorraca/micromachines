//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_SCREENEFFECT_H
#define MICROMACHINES_SCREENEFFECT_H

#include "Command.h"

class ScreenEffect : public Command{
    int32_t effect;
public:
    ScreenEffect(Scenario& scenario, Bot& bot, int32_t e) : Command(scenario, bot),
    effect(e){}
    void apply () override{
        scenario.showScreenEffect(effect);
    }
};

#endif //MICROMACHINES_SCREENEFFECT_H
