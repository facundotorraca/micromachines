//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_UPDATECAR_H
#define MICROMACHINES_UPDATECAR_H


#include <client/Entities/CarInfo.h>
#include "Command.h"

class UpdateCar : public Command{
    CarInfo info;
    public:
        explicit UpdateCar(CarInfo info, Scenario& scenario, Bot& bot): Command(scenario, bot), info(info){}

    void apply() override {
        scenario.updateCar(info);
        bot.update_car(info);
    }
};


#endif //MICROMACHINES_UPDATECAR_H
