//
// Created by javier on 18/11/19.
//

#ifndef MICROMACHINES_CARSLOWDOWN_H
#define MICROMACHINES_CARSLOWDOWN_H


#include <client/Scenario.h>

class CarSlowdown : public Command{
    int32_t id;
public:
    CarSlowdown(Scenario &scenario, int32_t id) : Command(scenario), id(id){}
    std::unique_ptr<Menu> apply() override {
        scenario.carSlowdown(id);
        return std::unique_ptr<Menu>();
    }
};


#endif //MICROMACHINES_CARSLOWDOWN_H
