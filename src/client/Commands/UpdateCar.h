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
        explicit UpdateCar(CarInfo info, Map& map, Bot& bot): Command(map, bot), info(info){}

    void apply() override {
        map.updateCar(info);
        bot.update_car(info);
    }
};


#endif //MICROMACHINES_UPDATECAR_H
