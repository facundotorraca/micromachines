#ifndef MICROMACHINES_COUNTDOWNTIMER_H
#define MICROMACHINES_COUNTDOWNTIMER_H

#include <cstdint>

class CountdownTimer : public Thread {

    int32_t max_time;

    std::unordered_map<int32_t, ThreadPlayer>& thread_players;
    std::unordered_map<int32_t, ProtectedQueue<UpdateClient>>& updates_players;

    private:
        void send_remaining_time(int32_t remaining_time);

        void wake_up_players();

        void run() override;

    public:
        explicit CountdownTimer(int32_t time,
                                std::unordered_map<int32_t, ThreadPlayer>& thread_players,
                                std::unordered_map<int32_t, ProtectedQueue<UpdateClient>>& updates_players);




};


#endif //MICROMACHINES_COUNTDOWNTIMER_H
