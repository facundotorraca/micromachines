#ifndef MICROMACHINES_GAMERULES_H
#define MICROMACHINES_GAMERULES_H

#include <map>
#include <vector>

class GameRules {
    uint32_t total_laps;
    bool finished;
    std::map<int32_t, int32_t> laps;
    std::vector<uint32_t> positions;

    public:
        explicit GameRules(int32_t total_laps);

        bool add_lap(int32_t id);

        void take_lap(int32_t id);

        bool is_finished();

        int32_t get_winner();

        int32_t get_lap(int32_t id);

        void get_update(int32_t id);

        ~GameRules();
};

#endif //MICROMACHINES_GAMERULES_H
