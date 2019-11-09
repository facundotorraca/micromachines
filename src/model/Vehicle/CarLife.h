#ifndef MICROMACHINES_CARLIFE_H
#define MICROMACHINES_CARLIFE_H

#include <atomic>
#include <cstdint>
#include <server/ClientUpdater.h>
#include <model/DTO_Info.h>

class CarLife {

    float life;
    float max_life;
    std::atomic<bool> changed;

    public:
        explicit CarLife(float life);

        bool is_dead();

        void restart_life();

        void make_damage(float damage);

        void send_general_update(int32_t ID, ClientUpdater &updater);

        void get_dto_info(DTO_CarLife& info_life);

    void appy_plugin(DTO_CarLife &life_info);
};


#endif //MICROMACHINES_CARLIFE_H
