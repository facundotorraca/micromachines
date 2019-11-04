//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_COUNTDOWNCOMMAND_H
#define MICROMACHINES_COUNTDOWNCOMMAND_H

#include "Command.h"

class CountdownCommand : public Command{
    int32_t number;
public:
    CountdownCommand(Scenario& scenario, Bot& bot, int32_t number) : Command(scenario, bot),
    number(number){}
    void apply () override{
        scenario.showCountdownNumber(number);
    }
};

#endif //MICROMACHINES_COUNTDOWNCOMMAND_H
