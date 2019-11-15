//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_SETTOTALLAPS_H
#define MICROMACHINES_SETTOTALLAPS_H

#include "Command.h"

class SetTotalLaps : public Command{
    int32_t laps;
public:
    explicit SetTotalLaps(Scenario& scenario, int32_t laps):
            Command(scenario),
            laps(laps){}

    std::unique_ptr<Menu> apply() override {
        scenario.setTotalLaps(laps);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_SETTOTALLAPS_H
