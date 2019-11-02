#ifndef MICROMACHINES_LAPCOUNTER_H
#define MICROMACHINES_LAPCOUNTER_H

#include <map>
#include <vector>

class LapCounter {
    bool finished;
    int32_t total_laps;
    std::map<int32_t /*ID*/, int32_t> laps;
    std::vector<uint32_t> positions;

    public:
        explicit LapCounter(int32_t total_laps);

        bool add_lap(int32_t id);

        void take_lap(int32_t id);

        bool is_finished();

        int32_t get_winner();

        int32_t get_lap(int32_t id);

        void get_update(int32_t id);

        ~LapCounter();
};

#endif //MICROMACHINES_LAPCOUNTER_H
