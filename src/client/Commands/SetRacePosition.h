//
// Created by javier on 9/11/19.
//

#ifndef MICROMACHINES_SETRACEPOSITION_H
#define MICROMACHINES_SETRACEPOSITION_H


#include "Command.h"

class SetRacePosition : public Command {
    int32_t position;
public:
    SetRacePosition(Scenario& scenario, Bot& bot, int32_t n) :
    Command(scenario, bot), position(n){}

    void apply(){
        scenario.setRacePosition(position);
    }
};


#endif //MICROMACHINES_SETRACEPOSITION_H
