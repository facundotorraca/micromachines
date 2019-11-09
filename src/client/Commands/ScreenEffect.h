#ifndef MICROMACHINES_SCREENEFFECT_H
#define MICROMACHINES_SCREENEFFECT_H

#include "Command.h"

class ScreenEffect : public Command{
    int32_t effect;
    int32_t duration;
public:
    ScreenEffect(Scenario& scenario, Bot& bot, int32_t effect, int32_t duration) : Command(scenario, bot),
    effect(effect), duration(duration){}
    void apply () override{
        scenario.showScreenEffect(effect, duration);
    }
};

#endif //MICROMACHINES_SCREENEFFECT_H
