#ifndef MICROMACHINES_LAPCOUNTER_H
#define MICROMACHINES_LAPCOUNTER_H

#include <map>
#include <vector>
#include <server/UpdateClient.h>

class LapCounter {
    int32_t total_laps;
    std::map<int32_t /*ID*/, int32_t> laps;

    public:
        explicit LapCounter(int32_t total_laps);

        void add_lap(int32_t ID);

        void take_lap(int32_t ID);

        UpdateClient get_update(int32_t ID);

        bool car_complete_laps(int32_t ID);

        int32_t get_total_laps();
};

#endif //MICROMACHINES_LAPCOUNTER_H
