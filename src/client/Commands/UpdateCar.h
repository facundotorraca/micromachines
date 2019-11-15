//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_UPDATECAR_H
#define MICROMACHINES_UPDATECAR_H


#include <client/Entities/CarInfo.h>
#include "Command.h"

class UpdateCar : public Command{
    CarInfo info;
    Camera& camera;
    public:
        explicit UpdateCar(CarInfo info, Scenario& scenario, Camera& camera):
        Command(scenario), info(info), camera(camera){}

    std::unique_ptr<Menu> apply() override {
        scenario.updateCar(info, camera);
        return std::unique_ptr<Menu>();
    }
};


#endif //MICROMACHINES_UPDATECAR_H
