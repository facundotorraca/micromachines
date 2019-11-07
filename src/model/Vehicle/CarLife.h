#ifndef MICROMACHINES_CARLIFE_H
#define MICROMACHINES_CARLIFE_H

#include <cstdint>
#include <server/ClientUpdater.h>

class CarLife {

    float life;
    float max_life;

    public:
        explicit CarLife(float life);

        bool is_dead();

        void restart_life();

        void make_damage(float damage);

        void send_general_update(int32_t ID, ClientUpdater &updater);
};


#endif //MICROMACHINES_CARLIFE_H
