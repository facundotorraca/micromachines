#ifndef MICROMACHINES_UPDATERACE_H
#define MICROMACHINES_UPDATERACE_H

#include <map>
#include <vector>
#include <unordered_map>
#include "model/Vehicle/Car.h"

class Race;
class Match;
class Player;

class UpdateRace {
    int32_t key;
    int32_t key_state;
    int32_t client_ID;

public:
    UpdateRace(int32_t client_ID, int32_t key, int32_t key_state);

    void update_cars(std::unordered_map<int32_t, Car>& cars);

    void update_player_view(std::unordered_map<int32_t, Player>& players);

    bool apply_restart_option(Race& race, std::unordered_map<int32_t, Player>& players, Match* match);

    bool is_from(int32_t ID);
};


#endif //MICROMACHINES_UPDATERACE_H
