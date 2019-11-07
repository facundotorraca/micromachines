#ifndef MICROMACHINES_RACE_H
#define MICROMACHINES_RACE_H

#include <unordered_map>
#include "RacingTrack.h"
#include <server/UpdateRace.h>
#include <model/Modifiers/ModifierSpawner.h>

class Race {
    LapCounter lap_counter;
    RacingTrack racing_track;
    ModifierSpawner modifier_spawner;

    std::unordered_map<int32_t, Car> cars;
    std::unordered_map<int32_t, Car&> running_cars;

    public:
        explicit Race(int32_t total_laps, std::string map_path, std::string map_name);

        void start();

        void update();

        void prepare();

        void update_cars(UpdateRace race);

        void player_left_game(int32_t ID);

        bool car_complete_laps(int32_t ID);

        UpdateClient get_update(int32_t ID);

        UpdateClient get_lap_update(int32_t ID);

        UpdateClient get_spawned_modifiers();

        void add_car_with_specs(int32_t ID, CarSpecs specs);

        void send_info_to_player(int32_t ID, ProtectedQueue<UpdateClient>& updates_player);

    UpdateClient get_life_update(int32_t ID);
};


#endif //MICROMACHINES_RACE_H
