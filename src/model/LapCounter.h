#ifndef MICROMACHINES_LAPCOUNTER_H
#define MICROMACHINES_LAPCOUNTER_H

#include <map>
#include <vector>
#include "DTO_Info.h"
#include <server/UpdateClient.h>
#include <server/ClientUpdater.h>

class LapCounter {

    int32_t total_laps;
    std::map<int32_t /*ID*/, int32_t> laps;

    public:
        explicit LapCounter(int32_t total_laps);

        void add_lap(int32_t ID);

        void take_lap(int32_t ID);

        bool car_complete_laps(int32_t ID);

        int32_t get_total_laps();

        void send_update(int32_t ID, ClientUpdater& client_updates);

        void send_total_laps(int32_t ID, ClientUpdater &updater);

        void get_dto_info(DTO_Info& param);
};

#endif //MICROMACHINES_LAPCOUNTER_H
