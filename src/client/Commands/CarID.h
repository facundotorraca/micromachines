//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_CARID_H
#define MICROMACHINES_CARID_H

#include "Command.h"

class CarID : public Command {
    int32_t id;
    public:
        explicit CarID(int32_t id, Scenario& scenario) : Command(scenario), id(id){}

        std::unique_ptr<Menu> apply() override {
            scenario.setOwnID(id);
            return std::unique_ptr<Menu>();
        }
};

#endif //MICROMACHINES_CARID_H
