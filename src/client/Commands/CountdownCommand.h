//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_COUNTDOWNCOMMAND_H
#define MICROMACHINES_COUNTDOWNCOMMAND_H

#include "Command.h"

class CountdownCommand : public Command{
    int32_t number;
public:
    CountdownCommand(Scenario& scenario, int32_t number) : Command(scenario),
    number(number){}
    std::unique_ptr<Menu> apply () override{
        scenario.showCountdownNumber(number);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_COUNTDOWNCOMMAND_H
