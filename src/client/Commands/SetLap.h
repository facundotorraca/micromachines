//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_SETLAP_H
#define MICROMACHINES_SETLAP_H

#include "Command.h"

class SetLap : public Command{
    int32_t lap;
public:
    explicit SetLap(Scenario& scenario, int32_t lap):
            Command(scenario),
            lap(lap){}

    std::unique_ptr<Menu> apply() override {
        scenario.setLapNumber(lap);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_SETLAP_H
