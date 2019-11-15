#ifndef MICROMACHINES_SCREENEFFECT_H
#define MICROMACHINES_SCREENEFFECT_H

#include "Command.h"

class ScreenEffect : public Command{
    int32_t effect;
    int32_t duration;
public:
    ScreenEffect(Scenario& scenario, int32_t effect, int32_t duration) : Command(scenario),
    effect(effect), duration(duration){}
    std::unique_ptr<Menu> apply () override{
        scenario.showScreenEffect(effect, duration);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_SCREENEFFECT_H
