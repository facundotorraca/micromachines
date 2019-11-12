#include <chrono>
#include <thread>
#include <server/ThreadPlayer.h>
#include <common/MsgTypes.h>
#include "CountdownTimer.h"

#define ONE_SECOND 1000

CountdownTimer::CountdownTimer(int32_t time, Race& race, ClientUpdater& client_updater):
    race(race),
    client_updater(client_updater)
{
    //this->race.prepare(this->client_updater);
    this->max_time = time;
}

void CountdownTimer::run() {
    int32_t remaining_time = this->max_time;
    this->send_remaining_time(remaining_time);
    while (remaining_time > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(int(ONE_SECOND)));
        remaining_time-= 1;
        this->send_remaining_time(remaining_time);
    }
    this->race.start();
}

void CountdownTimer::send_remaining_time(int32_t remaining_time) {
    UpdateClient update_countdown(std::vector<int32_t>{MSG_COUNTDOWN, remaining_time});
    this->client_updater.send_to_all(update_countdown);
}