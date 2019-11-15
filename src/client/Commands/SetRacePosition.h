//
// Created by javier on 9/11/19.
//

#ifndef MICROMACHINES_SETRACEPOSITION_H
#define MICROMACHINES_SETRACEPOSITION_H


#include "Command.h"

class SetRacePosition : public Command {
    int32_t position;
public:
    SetRacePosition(Scenario& scenario, int32_t n) :
    Command(scenario), position(n){}

    std::unique_ptr<Menu> apply(){
        scenario.setRacePosition(position);
        return std::unique_ptr<Menu>();
    }
};


#endif //MICROMACHINES_SETRACEPOSITION_H
