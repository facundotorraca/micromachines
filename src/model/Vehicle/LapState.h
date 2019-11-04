#ifndef MICROMACHINES_LAPSTATE_H
#define MICROMACHINES_LAPSTATE_H

#include <bits/unique_ptr.h>
#include "model/LapCounter.h"

class LapRunning;
class LapRestarted;
class LapCompleted;

class LapState {
    public:
        virtual std::unique_ptr<LapState> modify_car_laps(LapCounter& lap_counter, int32_t car_id) = 0;
};

class LapRunning: public LapState {

    public:
        std::unique_ptr<LapState> modify_car_laps(LapCounter& lap_counter, int32_t car_id) override {
            /* dont do anything */
            return std::unique_ptr<LapState> (new LapRunning());
        }

};

class LapCompleted : public LapState {

    public:
        std::unique_ptr<LapState> modify_car_laps(LapCounter& lap_counter, int32_t car_id) override {
            lap_counter.add_lap(car_id);
            return std::unique_ptr<LapState> (new LapRunning());
        }

};

class LapRestarted : public LapState {

    public:
        std::unique_ptr<LapState> modify_car_laps(LapCounter& lap_counter, int32_t car_id) override {
            lap_counter.take_lap(car_id);
            return std::unique_ptr<LapState> (new LapRunning());
        }

};

#endif //MICROMACHINES_LAPSTATE_H
