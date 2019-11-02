#include <chrono>
#include <thread>
#include "CountdownTimer.h"

#define ONE_SECOND 1000

CountdownTimer::CountdownTimer(int32_t time) {
    this->max_time = time;
    this->remaining_time = time;
}

bool CountdownTimer::continue_counting() {
    std::this_thread::sleep_for(std::chrono::milliseconds(int(ONE_SECOND)));
    this->remaining_time-= 1;
    return this->remaining_time > 0;
}
