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
        explicit UpdateCar(CarInfo info, Map& map): Command(map), info(info){}

    void apply() override {
        map.updateCar(info);
    }
};


#endif //MICROMACHINES_UPDATECAR_H
