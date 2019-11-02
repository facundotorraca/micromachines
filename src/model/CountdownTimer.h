#ifndef MICROMACHINES_COUNTDOWNTIMER_H
#define MICROMACHINES_COUNTDOWNTIMER_H

#include <cstdint>

class CountdownTimer {

    int32_t max_time;
    int32_t remaining_time;

    public:
        explicit CountdownTimer(int32_t time);

        bool continue_counting();
};


#endif //MICROMACHINES_COUNTDOWNTIMER_H
