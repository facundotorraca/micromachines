//
// Created by javif on 30/10/2019.
//

#ifndef MICROMACHINES_SETBACKGROUND_H
#define MICROMACHINES_SETBACKGROUND_H

#include "Command.h"

class SetBackground : public Command{
    int32_t type;
    int32_t width;
    int32_t height;
    Camera& camera;
public:
    explicit SetBackground(Scenario& scenario, Camera& camera, int32_t type, int32_t width, int32_t height):
            Command(scenario),
            type(type),
            width(width),
            height(height),
            camera(camera){}

    std::unique_ptr<Menu> apply() override {
        scenario.setBackground(type, width, height, camera);
        return std::unique_ptr<Menu>();
    }
};

#endif //MICROMACHINES_SETBACKGROUND_H
