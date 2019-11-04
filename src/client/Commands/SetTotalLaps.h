//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_SETTOTALLAPS_H
#define MICROMACHINES_SETTOTALLAPS_H

class SetTotalLaps : public Command{
    int32_t laps;
public:
    explicit SetTotalLaps(Scenario& scenario, Bot& bot, int32_t laps):
            Command(scenario, bot),
            laps(laps){}

    void apply() override {
        scenario.setTotalLaps(laps);
    }
};

#endif //MICROMACHINES_SETTOTALLAPS_H
