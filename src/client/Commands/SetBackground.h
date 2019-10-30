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
public:
    explicit SetBackground(Scenario& scenario, Bot& bot, int32_t type, int32_t width, int32_t height):
            Command(scenario, bot),
            type(type),
            width(width),
            height(height){}

    void apply() override {
        scenario.setBackground(type, width, height);
    }
};

#endif //MICROMACHINES_SETBACKGROUND_H
