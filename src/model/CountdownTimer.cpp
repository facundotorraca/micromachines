#include <chrono>
#include <thread>
#include <server/ThreadPlayer.h>
#include <common/MsgTypes.h>
#include "CountdownTimer.h"

#define ONE_SECOND 1000

CountdownTimer::CountdownTimer(int32_t time, Race& race,
                               std::unordered_map<int32_t, ProtectedQueue < UpdateClient>>& updates_players):
    race(race),
    updates_players(updates_players)
{
    this->max_time = time;
}

void CountdownTimer::run() {
    this->race.prepare();
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
    UpdateClient update_countdown({MSG_COUNTDOWN, remaining_time});
    for (auto& queue : this->updates_players){
        queue.second.push(update_countdown);
        std::cout << "TIME: " << remaining_time << "\n";
    }
}