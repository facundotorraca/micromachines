#ifndef MICROMACHINES_COUNTDOWNTIMER_H
#define MICROMACHINES_COUNTDOWNTIMER_H

#include "Race.h"
#include <cstdint>

class CountdownTimer : public Thread {

    int32_t max_time;

    Race& race;
    ClientUpdater& client_updater;

    private:
        void send_remaining_time(int32_t remaining_time);

        void run() override;

    public:
        explicit CountdownTimer(int32_t time, Race& race, ClientUpdater& client_updater);




};


#endif //MICROMACHINES_COUNTDOWNTIMER_H
