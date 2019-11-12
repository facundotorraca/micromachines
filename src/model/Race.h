#ifndef MICROMACHINES_RACE_H
#define MICROMACHINES_RACE_H

#include <unordered_map>
#include "RacingTrack.h"
#include "DTO_Info.h"
#include "PositionManager.h"
#include <server/UpdateRace.h>
#include <server/ClientUpdater.h>
#include <model/Modifiers/ModifierSpawner.h>

class Race {
    LapCounter lap_counter;
    RacingTrack racing_track;
    ModifierSpawner modifier_spawner;
    PositionManager position_manager;

    std::unordered_map<int32_t, Car> cars;

    public:
        explicit Race(int32_t total_laps, std::string map_path, std::string map_name);

        void start();

        void update();

        void update_cars(UpdateRace race);

        void prepare(ClientUpdater& updater);

        void player_left_game(int32_t ID);

        bool car_complete_laps(int32_t ID);

        void get_dto_data(DTO_Info& info);

        void apply_plugin(DTO_Info& info);

        void add_car_with_specs(int32_t ID, CarSpecs specs);

        void send_updates(int32_t ID, ClientUpdater &updater);

        void send_info_to_player(int32_t ID, ClientUpdater& client_updater);
};


#endif //MICROMACHINES_RACE_H
