//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_SETLAP_H
#define MICROMACHINES_SETLAP_H

class SetLap : public Command{
    int32_t lap;
public:
    explicit SetLap(Scenario& scenario, Bot& bot, int32_t lap):
            Command(scenario, bot),
            lap(lap){}

    void apply() override {
        scenario.setLapNumber(lap);
    }
};

#endif //MICROMACHINES_SETLAP_H
