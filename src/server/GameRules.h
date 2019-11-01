#ifndef MICROMACHINES_GAMERULES_H
#define MICROMACHINES_GAMERULES_H

#define INVALID_ID -1

#include <map>
#include <vector>

class GameRules {
    uint32_t total_laps;
    bool finished;
    std::map<uint32_t, uint32_t> laps;
    std::vector<uint32_t> positions;

    public:
        explicit GameRules(uint32_t total_laps);
        bool add_lap(uint32_t id);
        bool is_finished();
        int32_t get_winner();
        uint32_t get_lap(uint32_t id);
        ~GameRules();
};

#endif //MICROMACHINES_GAMERULES_H
